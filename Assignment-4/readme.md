## Assignment-4


# Chocolate-Addicted Passengers: A Transportation System Simulation

This project simulates a transportation system where passengers are addicted to chocolate! The project is designed using Object-Oriented Programming (OOP) concepts and models three main concepts: Passengers, Trains, and Stations.

## Passengers
Each passenger has a specified amount of chocolate usage per time unit and a known route of stations to pass through. Passengers must buy chocolates at each station based on the waiting time until the next station.

## Trains
Trains move between two specific stations. When a train reaches one end, it rests for a given number of time units called `cooldown time` before moving to the other end. The travel time between the two ends is called `travel time`.

## Stations
Stations are where trains move between and where passengers buy chocolates. Each station has a name and sells chocolates to passengers for a certain price.

## Additional Constraints
- When a train reaches a station, all passengers get off and the next group gets on at the next time unit.
- Passengers wait for one time unit after getting off the train before searching for a suitable train.
- Passengers only buy chocolates while at the station, not while on the train.
- Passengers and trains have unique IDs.
- Train collisions are not considered and trains move past each other if needed.
- If multiple trains are eligible for passengers to board, passengers will choose the train with the lowest ID.
- There is a global clock in the simulation starting from t = 0.
- `chocolate addiction` is an integer value.

Sure! Here is the enhanced version of the rest of your README in raw format:

## Available Commands

This simulation includes several generic commands:

| Input  | Output |
| ------------- | ------------- |
| add_passenger <taffy addiction> <1st station name> <2nd station name> <3rd station name> ...|OK|
| add_station < name> <taffy_price>|OK|
| add_train < starting station name> < second station name> < travel time> < cooldown time>|OK|
| advance_time < time_steps>|OK|
| finish|OK|

The first three commands take the necessary arguments and create the corresponding class. The `advance_time` command advances time so that trains move to the other end or passengers get on the train. The `finish` command advances time as much as needed so that all passengers reach their destination.

### Special Commands for Passengers

There is also a special command for passengers:

| Input  | Output |
| ------------- | ------------- |
|show_passenger_info <person id>|status: <on train/in station/arrived><br>spent: < amount><br>current <station/train> <name/id>|

This command shows:
- If the passenger is moving, in the station, or has reached their destination.
- The amount of money the passenger spent on chocolate.
- Where the passenger is. If it is a station, it will print out "station" alongside the name of the station. Otherwise, it will print "train" and the ID of the train.

### Special Commands for Trains

There is also a special command for trains:

| Input  | Output |
| ------------- | ------------- |
|show_train_info <train id>|status: <resting/moving><br>estimated remaining time: < time><br>next station: < station name><br>passengers count: < number of passengers>|

This command shows if the train is moving or resting and how much time is remaining in either state. It also shows the next station and the number of passengers on the train.

In this project, we assume that inputs are valid and there is no need for exception handling.
