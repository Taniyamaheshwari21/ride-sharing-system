# ride-sharing-system

## Overview

This Ride Sharing App is a simple C++ console application designed to manage drivers, passengers, and rides. It provides functionalities such as adding drivers and passengers, requesting a ride, completing a ride, canceling a ride, and calculating ride fares. The application prioritizes ride requests on a first-come, first-served basis and assigns drivers based on proximity to the passenger's location.

## Features

- **Add Driver**: Add a new driver with details such as name, car details, and current location.
- **Add Passenger**: Add a new passenger with details such as name and current location.
- **Request a Ride**: Request a ride by specifying the passenger's current location and destination. The nearest available driver is assigned to the ride.
- **Complete a Ride**: Mark a ride as completed, making the driver available for new rides.
- **Cancel a Ride**: Cancel a pending ride, making the driver available for new rides.
- **Calculate Ride Fare**: Calculate the total fare based on the distance traveled.

## Distance and Fare Calculation

- The distance between two locations is calculated using the Euclidean distance formula.
- The fare structure is as follows:
  - Base Fare: ₹50 for the first kilometer
  - Additional Fare: ₹20 for each subsequent kilometer


### Usage

Follow the on-screen prompts to interact with the application. The main menu offers the following options:

1. **Add a Driver**: Enter driver details including name, car details, and current location (latitude and longitude).
2. **Add a Passenger**: Enter passenger details including name and current location (latitude and longitude).
3. **Request a Ride**: Enter the passenger's name and the locations for the current location and destination.
4. **Complete a Ride**: Enter the car details to mark a ride as completed and calculate the fare.
5. **Cancel a Ride**: Enter the car details to cancel a pending ride.
6. **Calculate Ride Fare**: Enter the passenger's name and car details to calculate the fare for the ride.
7. **Exit**: Exit the application.

## Code Structure

- **Structs**:
  - `Location`: Represents a geographical location with latitude and longitude.
  - `driver`: Represents a driver with details such as name, car details, availability, and location.
  - `passenger`: Represents a passenger with details such as name and location.
  - `ride`: Represents a ride with details such as passenger name, car details, status, current location, and destination.

- **Functions**:
  - `distance`: Calculates the distance between two locations.
  - `calculateFare`: Calculates the total fare for a ride.
  - `completeride`: Marks a ride as completed and makes the driver available.
  - `cancelride`: Cancels a pending ride and makes the driver available.
  - `check`: Checks if a passenger already exists in the data.
  - `addRide`: Adds a new ride request and assigns the nearest available driver.
  - `addDriver`: Adds a new driver.
  - `addPassenger`: Adds a new passenger.

- **Main Function**:
  - Contains the main loop with options to add drivers, add passengers, request rides, complete rides, cancel rides, and calculate ride fares.

## Future Improvements

- Implement a more sophisticated ride assignment algorithm considering factors such as traffic, estimated time of arrival, etc.
- Add a graphical user interface for better user experience.
- Implement persistent storage to save and load data.



---

Feel free to modify this README file to better fit your project's specifics and your personal style.
