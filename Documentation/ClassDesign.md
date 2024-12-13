
# Shooter(Abstract base class)
## Functionalities
        -   something to hold the position of the sattelite
        -   clock to hold down the time elapsed before last fired in order to check cooldown reached or not
        -   something to hold cooldown period value
        -   the type of missile attached 
        -   a method to check if the missile can fire or not
        -   a method to toggle cooldown
        -   overide methods in derived classes to draw the graphics of different kind of shooters
        -   overide a shoot methods in derived  classes which returns a list of msisiles to be added to missile manager based upon the inputed target
##    Data
        -   positon
        -   cooldown period
        -   clock to record time elapsed before last fired 
        -   cooldown_enabled
        -   attachedMissileType
        -   static size // defines size of image on screen 
##    Methods
        -   Shooter(position,cooldown period,missile)
        -   virtual shoot() // returns a instance of missile 
        -   setCooldownPeriod()
        -   virtual getType()
        -   virtual getImage()
        -   canShoot() //returns boolean value if missile can shoot or not
        -   ~Shooter() 
<!-- # NormalShoooter(extends Shooter)
    Data
        -   image
        -   type
    Methods
        -   Overides shoot()
# SpreadShoooter(extends Shooter)
    Data
        -   image
        -   type
        -   missileCount // number of missiles to be fired 
    Methods
        -   Overides shoot()
# RapidShoooter(extends Shooter)
    Data
        -   image
        -   type
        -   missileCount // number of missiles to be fired 
        -   interval    // interval between two missiles
    Methods -->
        -   Overides shoot()

# ShooterManager
## Functionalities
        -  maitaining a list of shooters on screen 
        -  a method which adds to the list of shooters and takes in a shootertype as input
        -  a handle target method which basically shoot on the designated target 
        -   remove shooter which will remove the shooter from screen
        -  a method which draws all the shooters on screen on the inputed window
        Future functionalilty 
            - a slot based system where the user can choose which shooters to have in slots
    "responsible for maintaining the list of sattelits on screen and doing group actions on them"
##    Data
        -   list<Shooters>
        -   enum shooterTypes
        -   Shooter SelectedShooter 
##    Method
        -   ShooterManager()
        -   addNewShooter(type) // adds new shooter to the screen
        -   handleTarget(targetPos) // handles the target by shooting missiles  
        -   removeShooter() //removes currentSelectedShooter from the screen
        -   Map(function_ptr) //applies that function to all the shooters  
        -   setSelectedShooter()
        -   drawShooters(window) // dras shooters on the window
# Asteriod(base class) 
## Functionality 
        - something to hold the graphics of asteroid in order for drawing
        - something for speed we need to create different asteroid with different speeds
        - something for hitpoints so as to know if a asteroid needs to be destroyed or not
        -  position vector2f this would indicate where to render graphics of asteroid on screen startpositon should be randomized   in Asteroid Manager
        - direction of movement a vector2f should be randomized  in Asteroid Manager
        -   a move method which would calculate new position of asteroid based upon direction of movement current position and speed
        - a draw method / render method which would take in a window and draw the graphics of asteroid based on current positon
        - a method to call when a asteroid collides basically reduce the hitpoints
        - optionaly a method to call when asteroid gets destroyed some kind of animation or sound maybe
    Instead of creating all these classes lets just have different functions in Asteroid Manager which create such classes 
##    Data 
        -   type 
        -   health
        -   speed 
        -   trajectory(current pos+angle of movement )
        -   pointsAwarded
        -   image
        -   size
        -   bool hasChild // is true if on burst produces  new asteroids
##    Methods 
        -   Asteroid()
        -   move() //sets new pos for frame change
        -   getImage()
        -   getType()
        -   setTrajectory()
        -   setSpeed()
        -   setHealth() 
        -   ~Asteriod

    "defines movement,appearance and behaviour on destruction of asteroids"

# AsteroidManager
## Functionalities
        - something like a list to hold all the asteroids that are alive on screen
        - to create different types of asteroids (by setting different speeds , hitpoints) (defining methods for it )
        - an add method which would randomly spawn asteroid and add it to list of  new asteroids 
        - a  method to check if any asteroid is colliding with the earth  in order to trigger game over 
        - a method which would check if any asteroid collies with the specified impactArea and thereby handle the asteroid behaviour (maybe delete it or reduce its hp or call some method of asteroid)
        - a method which would render all the asteroids on the screen call the draw method of all asteroids 
        - a method which would move all the asteroids call the move funcion of all asteroids
        - method which would take in a window as input and draw all asteroids on  it
        - a method to return the points accumualted in that frame 
    "responsible for maintaining the list of asteroids that are currently on screen"
##    Data:
        -   list<Asteroids>
        -   enum asteroidTypes (declared globally )
##    Methods:
        -   addAsteroid(asteroidType) // creates different type of asteroid by setting different speed,health etc
        -   hitsEarth() // checks if any asteroid hits the earth 
        -   checkCollison() // checks the event when a asteroid collides missile and handles it and then returns the pointScored
        -   private destroyAsteroid(Asteroid asteroid)
        -   moveAsteroids() // moves all the asteroids when frame changes
        -   Map(function) applies that function to all the asteroids 
        -   drawAsteroids(window) // dras shooters on the window


# Missile(Abstract base class)
## Functionalities
            - define a speed (use vector2f) for missile helpful in calculating next position of missile in next frame
            - define a impact Radius which is the area of blast and getImapctRadius
            - something to hold targetCoordinates(the position of blast)
            - something to hold type (the type of missile)
            -  somethig to hold position (use vector2f) this would indicate where to render graphics of missile on 
            - something to hold directionOfMovemet (use vector2f) this would indicate the movement vector
            - a method move which calculates the next position of missile based on current pos direction of movement and speed
            - something to hold the state of missile wheter its alive or in blast state in order to render different graphcics accordingly to state
            - something to hold whether  a missile has special effects on blast or not 

            - a draw function which renders the graphics of missile have differnt graphics for different missiles (use a virtual fnc in missile class and overide it in different derived classes)
            - something to hold graphics of missile different classes to have different missile 
            - we should be able t customise the position the direction of movement during creation of missile as thoose will depend on user inputs
            - optionally overide the effect on blast method in derived classes to call when missile blasts 
                like some special effects sound animation 
##   Data:
        -   speed
        -   size
        -   trajectory = (currentPos,angleOfMovement) 
        -   impactRadius // rename to blastRadius
        -   bool specialEffectOnBlast
        -   targetCoordinates
        -   image
        -   type
##    Method:
        -   Missile()
        -   move()
        -   virtual getImage()
        -   virtual getType()
        -   setTrajectory()
        -   setImapctPerimeter
        -   virtual effectOnBlast()
<!-- # NormalMissile(extends Missile)
    Method
        -   NormalMissile()
        -   overides effectOnBlast()

# BigBlaster(extends Missile)
    Method
        -   BigBlaster()
        -   overides effectOnBlast()

#  Missile2(extends Missile)
    Method
        -   Missile2()
        -   overides effectOnBlast() -->

# MissileManager
## Functionalities
        -   a list   that will hold all the missile that are currently on screen
        -   an addMissile method that will add the missile objects list passed as input into the missile list all that the creation of missile would be handled by shooter
        -  a move method basically tasked with calling the move of all the missible objects that are on screen
        - a checkTarget reached function which basically checks if the missile has reached its desitantion and then calls its effectOnBlast and then maybe delete it 
        -   a remove missile method that removes the missile from the list 
        -   drawMissiles bascially a method which calls the draw method of all missible objects we will define the graphics of missiles in the missile class itself
        -  a optional map function which takes in a funcion and call that method on every missile useful if we want to decrease the speed of every missile  we will just pass a functin which does this
##    Data
        -   list (Missiles)
##    Method
        -   addMissile(Missile) // 
        -   move() // changes the position of missiles when frame changes
        -   removeMissile()
        -   handleTargetReached() // handles the behaviour of missile when target is reached
        -   Map(function_ptr) // aplies the funciton on all the missiles
        -   drawMissiles(window) // draw missiles on the window
# GameLogic
    Data
        -   GameScore
        -   bool GameOver
        -   file highScoreKeeper
        -   MissileManager 
        -   AsteroidManager
        -   ShooterManager
    Method
        -   GameLogic()
        -   actionOnKeys(key) //defines behaviour of game when keys are used by user
        -   mouseListener()   // defines behaviour of game on mouse clicks by user
        -   handleFrameEvents() //  defines tasks to do between frames
        -   handlegameOver()    // defines tasks to do when game is over

<!-- # PowerUp:
    Data
    - duration: int (duration of the power-up effect in seconds)
    - active: bool (indicates if the power-up is currently active)
    
    Methods
    - activate(): Activates the power-up effect.
    - deactivate(): Deactivates the power-up effect.
    - update_status(): Checks if the power-up duration has ended.


# NoCooldownPowerUp(PowerUp):
    Data
    - target_satellite: Shooter (reference to the satellite getting the powerup)
    
    Methods
    - activate_nocooldown(): Removes cooldown for the target satellite.
    - deactivate_nocooldown(): Restores the original cooldown for the target satellite.


# CooldownReductionPowerUp(PowerUp):
    Data
    - target_shooter: List[Shooter] (list of shooter affected by cooldown reduction)
    - reduction_factor: float (factor by which cooldown is reduced)
    
    Methods
    - activate_redcooldown(): Reduces cooldown for target shooter.
    - deactivate_redcooldown(): Restores the original cooldown for the target shooter. -->

<!-- # BossAsteroid (derived from base class: Asteroid )
    Data
        -image 
    Methods 
        -Constructor
            - base class +
            - set bigger health 
            - set low Speed
            - set points on destruction
            - subasteroids 
            - subasteroid movements

# SplitAsteroid (derived from base class: Asteroid)
    Methods 
        -overrides destruction (creates two new asteroids) -->


# GameLogic 
    constructor
        intialises shootermanager asteroid manager missle manager
        intialises the file pointer
    frame logic 
        implements all the logic between 2 frames 