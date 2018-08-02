#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include "Vector2f.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "Obstacle.h"
#include "Bird.h"
#include "Input.h"
#include "utility/Log.h"
#include "NeuralNetwork.h"

float obstacleDistance = 13;

int num_of_birds = 50;
Texture* pipeTexture;
std::vector<NeuralNetwork> evolve(std::vector<NeuralNetwork>& networks){
    std::vector<NeuralNetwork> result;
    std::vector<int> pool;
    long fitnesses[num_of_birds];
    long long sum = 0;
    long maxfit = 0;
    int maxfiti = 0;
    for(int i =0 ;i<num_of_birds; i++){
        fitnesses[i] = networks[i].getFitness() * networks[i].getFitness() ;

        if(fitnesses[i] > maxfit){
            maxfit = fitnesses[i];
            maxfiti = i;
        }

        sum += fitnesses[i];
    }
    std::cout<<std::endl;
    for(int i =0 ;i<num_of_birds; i++){
        fitnesses[i] = 1000 * fitnesses[i] / sum;
        for(int j = 0; j< fitnesses[i]; j++){
            pool.push_back(i);
        }
    }
    std::cout<<sum << std::endl;
    for(int i =0 ;i<num_of_birds; i++){
        //result[i] = networks[pool[rand()%pool.size()]]->crossover(networks[pool[rand()%pool.size()]]);
        unsigned long chosenIndex = rand()%pool.size();
        if(pool[chosenIndex] == maxfiti)std::cout<<"chose";
        std::cerr<<pool.size()<<" "<<chosenIndex<<std::endl;
        result.push_back(networks[pool[chosenIndex]]);
        result[i].mutate();
    }
    for(auto i:  pool){
        std::cout<<i<<" ";
    }
    std::cout<< std::endl;
    return result;
}

void initGame(std::list<Obstacle*>& obstacles, Bird** birds){
    for(int i = 0; i<num_of_birds; i++){
        birds[i]->reset();
    }
    for(auto i : obstacles){
        delete i;
    }
    obstacles.clear();

    for(int i = 0; i < 5; i++){
        obstacles.emplace_back(new Obstacle(pipeTexture, 30 + i * obstacleDistance));
    }
}

void checkObstacles(std::list<Obstacle*>& obstacles, Bird& bird){
    while(!obstacles.empty() && obstacles.front()->posLessThanX(-2)){
        obstacles.pop_front();
        obstacles.emplace_back(new Obstacle(pipeTexture, obstacles.back()->getX() + obstacleDistance));
    }
    for(auto i : obstacles){
        if (!i->isPassed() && (i->getX() + i->getWidth() - bird.getX() + bird.getWidth()) < 0){
            i->setPassed(true);
        }
        if (!i->isPassed()){
            bird.setDistance(i->getX() - bird.getX(), i->getHeight() - bird.getY());
            break;
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    Window::initGLFW();
    Window::createWindow(800, 600, "FlappyAI");
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1.0, 0.0, 0.0, 1.0);

    Sprite::initBuffers();

    Shader* spriteShader = ResourceManager::loadShader("sprite_shader", "sprite_shader.vs", "sprite_shader.fs");
    Shader* parallaxShader = ResourceManager::loadShader("parallax_shader", "parallax.vs", "parallax.fs");
    spriteShader->bind();
    spriteShader->setVec2("screenSize", Vector2f(20, 15));

    pipeTexture = ResourceManager::loadTexture("pipe", "pipe.png");
    Texture* image = ResourceManager::loadTexture("bird", "bird.png");
    Texture* background = ResourceManager::loadTexture("background", "background.png");
    Sprite backgroundSprite(background, Vector2f(20, 15), Vector2f(21, 16));

    Bird* birds[num_of_birds];
    for(int i = 0; i<num_of_birds; i++){
        birds[i] = new Bird(image);
    }
    std::list<Obstacle*> obstacles;

    initGame(obstacles, birds);


    std::vector<NeuralNetwork> nns;
    for(int i = 0; i<num_of_birds; i++){
        nns.emplace_back(3, 3, 1);
    }

    float offset = 0;

    float speed = 0;

       while(!Window::isShouldClose()){
        if(Input::isKeyUp(GLFW_KEY_SPACE)) {
            speed = 1;
        }
        if(Input::isKeyUp(GLFW_KEY_UP)){
            speed++;
        }
        if(Input::isKeyUp(GLFW_KEY_DOWN)){
            speed--;
        }


        for(int i = 0; i < speed; i++){
            offset += 0.0001;

            for(auto i : obstacles){
                i->move(0.2);
            }

            bool guesses[num_of_birds];
            bool atLeastOne =  false;
            for(int i = 0; i<num_of_birds; i++){
                if(!birds[i]->dead) {
                    nns[i].increaseFitness();
                    atLeastOne = true;
                    checkObstacles(obstacles, *birds[i]);

//                    std::vector<float> input = {birds[i]->getXDistance(), birds[i]->getYDistance()};
                    std::vector<float> input = {birds[i]->getXDistance(), birds[i]->getYDistance(), birds[i]->getVelocity()};
                    guesses[i] = nns[i].Guess(input)[0] > 0.5;
                    //nns[i]->Guess()
                    if (guesses[i]) birds[i]->jump();
//                    if(Input::isKeyDown(GLFW_KEY_SPACE)){
//                        birds[0]->jump();
//                    }
                    birds[i]->move();
                    if(birds[i]->dead = birds[i]->shouldDie(obstacles)){
                        //finish(birds[i]->getXDistance(), birds[i]->getYDistance(), glfwGetTime() - startTime);
                    }


                }
            }
            if(!atLeastOne){
                Log::Message("", LOG_INFO);
                initGame(obstacles, birds);
                nns = evolve(nns);
                for(int i = 0; i < num_of_birds; i++){
                    nns[i].resetFitness();
                }
            }
            parallaxShader->bind();
            parallaxShader->setFloat("offset", offset);
        }


        //Draw the scene
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        backgroundSprite.render(parallaxShader);

        for(int i = 0; i<num_of_birds; i++){
            if(!birds[i]->dead)birds[i]->render(spriteShader);
        }
        for(auto i : obstacles){
            i->render(spriteShader);
        }

        Window::render();
        Input::update();

        glfwPollEvents();
    }

    Window::dispose();

    return 0;
}