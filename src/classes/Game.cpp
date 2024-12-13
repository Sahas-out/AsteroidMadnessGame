#include "Game.h"
#include<iostream>

void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(settings::windowWidth,settings::windowHeight),"astroid shooter",sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(settings::fps);
}

void Game::initScore()
{
    if (!font.loadFromFile(settings::fontFile)) { // Ensure you have this font in your project directory
        std::cout << "Error: Font file not found" << std::endl;
        return;
    }
    // Create a text object
    scoreText.setFont(font);                // Set the font
    scoreText.setCharacterSize(50);         // Set the text size
    scoreText.setFillColor(sf::Color::White); // Set the text color
    scoreText.setPosition(10.f, 10.f);      // Set the text position
}

void Game::clearScreen()
{
    delete asteroidManager;
    delete missileManager;
    delete shooterManager;
    this->asteroidManager = new AsteroidManager();
    this->missileManager = new MissileManager(this->window);
    this->shooterManager = new ShooterManager(this->window);
    asteroidManager->setWindow(this->window);
    this->score = 0;
}

void Game::displayScore()
{
    score = asteroidManager->getScore();
    scoreStream.str("");          // Clear previous content
    scoreStream.clear();          // Reset flags
    scoreStream << "Score:" << score <<"\nHighScore:" << highScore;
    scoreText.setString(scoreStream.str());
    window->draw(scoreText);
}

Game::Game()
{   
    this->initWindow();
    this->initBackground();
    this->asteroidManager = new AsteroidManager();
    asteroidManager->setWindow(this->window);
    this->missileManager = new MissileManager(this->window);
    this->shooterManager = new ShooterManager(this->window);

    this->initScore();
    cursorImage.loadFromFile(settings::cursorImage);
    cursor.loadFromPixels(cursorImage.getPixelsPtr(),cursorImage.getSize(),sf::Vector2u(cursorImage.getSize().x/2,cursorImage.getSize().y/2));
    window->setMouseCursor(cursor);
    backgroundMusic.openFromFile(settings::backgroundMusic);
    backgroundMusic.setVolume(40);
    backgroundMusic.setLoop(true);
    backgroundMusic.play();
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(100);
    gameOverText.setFont(font);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition
    (settings::windowWidth/2 - gameOverText.getGlobalBounds().getSize().x /2,
    settings::windowHeight/2 - gameOverText.getGlobalBounds().getSize().y/2);
    gameOver = false;
    
    std::ifstream scoreFile(settings::scoreFile);
    std::string line;
    std::getline(scoreFile,line);
    this->highScore = std::stoi(line);
    scoreFile.close();
}

Game::~Game()
{
    backgroundMusic.stop();
    std::ofstream scoreFile(settings::scoreFile);
    scoreFile << std::to_string(this->highScore) <<std::endl;
    delete this->window;
}
void Game::initBackground()
{
    if (!backgroundTexture.loadFromFile(settings::backgroundImage))
    {
        std::cout << "Error loading background!" << std::endl;
        return;
    }

    // Enable smooth scaling
    backgroundTexture.setSmooth(true);
    
    backgroundSprite.setTexture(backgroundTexture);

    
    
    backgroundSprite.setPosition(0, 0);
}
void Game::run()

{   
    while(this->window->isOpen())
    {
        sf::Event event;
        while (this->window->pollEvent(event))
        {
            if (event.Event::type == sf::Event::Closed)
                this->window->close();
            this->handleKeys(event);
        }
        
        this->window->clear();
        if(gameOver)
        {
            window->draw(backgroundSprite);
            window->draw(gameOverText);
            this->displayScore();
            window->display();
            continue;
        }
        this->window->draw(backgroundSprite); 

        this->missileManager->updateStatus();
        this->missileManager->executeMissileBehaviour();

        this->asteroidManager->handleCircleCollisons(this->missileManager->getAllBounds());
        this->asteroidManager->spawnAsteroids();
        this->asteroidManager->updateAsteroids();
        this->score = asteroidManager->getScore();
        gameOver =  this->asteroidManager->checkGameOver();

        if(gameOver){
            highScore = std::max(highScore,score);
            continue;
        }
        // gameOver = asteroidManager->gameOver;
        this->shooterManager->render();
        this->missileManager->render();
        this->asteroidManager->render();
        this->displayScore();                         
        window->display();
    }
}

void Game::handleKeys(sf::Event & event)
{
    int shooter;
    if(gameOver)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Escape)
            {
                this->window->close();
            }
            if(event.key.code == sf::Keyboard::Space)
            {
                this->clearScreen();
                this->gameOver = false;
            }
        }
        return;
    }
    if (event.type == sf::Event::KeyPressed) 
    {
        switch (event.key.code) 
        {
            case sf::Keyboard::Escape:
                this->window->close();
                break;
            case sf::Keyboard::A:
                shooter = shooterManager->getCurrentShooter();
                shooter = (shooter - 1 < 0) ? settings::totalShootersCount - 1 : shooter -1 ;
                shooterManager->selectShooter(shooter);
                break;
            case sf::Keyboard::D:
                shooter = shooterManager->getCurrentShooter();
                shooter = (shooter + 1 >= settings::totalShootersCount) ? 0 : shooter +1 ;
                shooterManager->selectShooter(shooter);
                break;
            case sf::Keyboard::Num1:
                shooterManager->selectShooter(0); 
                break;
            case sf::Keyboard::Num2: 
                shooterManager->selectShooter(1);
                break;
            case sf::Keyboard::Num3: 
                shooterManager->selectShooter(2);
                break;
            case sf::Keyboard::Num4: 
                shooterManager->selectShooter(3);
                break;
            case sf::Keyboard::Num5: 
                shooterManager->selectShooter(4);
                break;
            case sf::Keyboard::Num6:
                shooterManager->selectShooter(5);
                break;
            case sf::Keyboard::Num7:
                shooterManager->selectShooter(6);
                break;
        }
    }
    if (event.Event::type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*window));
        missileManager->addMissile(shooterManager->shoot(mousePosition));
    }
}


void Game::setHighScore(int inHighScore)
{
    this->highScore = inHighScore;
}
int Game::getHighScore()
{
    return this->highScore;

}