#Specify the version being used aswell as the language
cmake_minimum_required(VERSION 2.6)
#Name your project here
project(CitySimulator)

#This tells CMake to fib.c and name it fibonacci
add_executable(CitySimulator City/Ambulance.h City/Building.h City/Check.h City/City.h City/CityParser.h City/Depot.h City/DesignByCOntract.h City/FileTest.h City/FireDepot.h City/FireTruck.h City/GUI.h City/Hospital.h City/House.h City/Output.h City/Point.h City/PoliceDepot.h City/PoliceTruck.h City/Shop.h City/Simulator.h City/Size.h City/Street.h City/tinystr.h City/tinyxml.h City/vehicle.h City/CityX.cpp City/Ambulance.cpp City/Building.cpp City/Check.cpp City/City.cpp City/CityParser.cpp City/Depot.cpp City/FileTest.cpp City/FireDepot.cpp City/FireTruck.cpp City/GUI.cpp City/Hospital.cpp City/House.cpp City/Output.cpp City/Point.cpp City/PoliceDepot.cpp City/PoliceTruck.cpp City/Shop.cpp City/Simulator.cpp City/Size.cpp City/Street.cpp City/tinystr.cpp City/tinyxml.cpp City/tinyxmlerror.cpp City/tinyxmlparser.cpp City/vehicle.cpp)