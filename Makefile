include_path = "lib/SFML-2.6.1/include"
link_path = "lib/SFML-2.6.1/lib"
cpp_files_path = src/classes/
obj_files_path = bin/
hpp_files_path = src/include/
java_home = javaHome/
all: build

$(obj_files_path)GameUtils.o: $(cpp_files_path)GameUtils.cpp $(hpp_files_path)GameUtils.hpp
	g++  -c  $(cpp_files_path)GameUtils.cpp  -I $(include_path) -I $(hpp_files_path) -o $(obj_files_path)GameUtils.o

$(obj_files_path)Missile.o : $(cpp_files_path)Missile.cpp $(hpp_files_path)Missile.hpp $(obj_files_path)GameUtils.o
	g++  -c  $(cpp_files_path)Missile.cpp  -I $(include_path) -I $(hpp_files_path) -o $(obj_files_path)Missile.o

$(obj_files_path)MissileManager.o : $(cpp_files_path)MissileManager.cpp $(hpp_files_path)MissileManager.hpp $(obj_files_path)Missile.o
	g++  -c  $(cpp_files_path)MissileManager.cpp  -I $(include_path) -I $(hpp_files_path) -o $(obj_files_path)MissileManager.o


$(obj_files_path)Shooter.o : $(cpp_files_path)Shooter.cpp $(hpp_files_path)Shooter.hpp $(obj_files_path)Missile.o
	g++  -c  $(cpp_files_path)Shooter.cpp  -I $(include_path) -I $(hpp_files_path) -o $(obj_files_path)Shooter.o

$(obj_files_path)ShooterManager.o : $(cpp_files_path)ShooterManager.cpp $(hpp_files_path)ShooterManager.hpp $(obj_files_path)Shooter.o
	g++  -c  $(cpp_files_path)ShooterManager.cpp  -I $(include_path) -I $(hpp_files_path) -o $(obj_files_path)ShooterManager.o

$(obj_files_path)Asteroid.o : $(cpp_files_path)Asteroid.cpp $(hpp_files_path)Asteroid.h $(obj_files_path)GameUtils.o
	g++  -c  $(cpp_files_path)Asteroid.cpp  -I $(include_path) -I $(hpp_files_path) -o $(obj_files_path)Asteroid.o

$(obj_files_path)AsteroidManager.o : $(cpp_files_path)AsteroidManager.cpp $(hpp_files_path)AsteroidManager.h $(obj_files_path)Asteroid.o
	g++  -c  $(cpp_files_path)AsteroidManager.cpp  -I $(include_path) -I $(hpp_files_path) -o $(obj_files_path)AsteroidManager.o

$(obj_files_path)Game.o : $(cpp_files_path)Game.cpp $(hpp_files_path)Game.h $(obj_files_path)ShooterManager.o  $(obj_files_path)AsteroidManager.o $(obj_files_path)MissileManager.o  
	g++  -c  $(cpp_files_path)Game.cpp  -I $(include_path) -I $(hpp_files_path) -o $(obj_files_path)Game.o


$(obj_files_path)Main.o : $(cpp_files_path)Main.cpp $(obj_files_path)Game.o
	g++  -c $(cpp_files_path)Main.cpp  -I $(include_path) -I $(hpp_files_path) -o $(obj_files_path)Main.o

./app.exe : $(obj_files_path)Main.o  $(obj_files_path)Game.o $(obj_files_path)AsteroidManager.o $(obj_files_path)Asteroid.o $(obj_files_path)Missile.o $(obj_files_path)MissileManager.o $(obj_files_path)Shooter.o  $(obj_files_path)ShooterManager.o $(obj_files_path)GameUtils.o      
	g++ -o ./app.exe $(obj_files_path)*  -L $(link_path) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

build: ./app.exe
	$(info BUILD SUCCESFUL)
	$(info ---------------------------)

run: ./app.exe
	./app.exe
clean:
	rm -rf ./app.exe

cleanAll:
	rm -rf $(obj_files_path)*
	rm -rf ./app.exe

