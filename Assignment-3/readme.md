## Assignment 3
### description

in third assignment we are trying to simulate racism through an expirement designed by [Thomas Schelling](https://en.wikipedia.org/wiki/Thomas_Schelling).online version of this simulation is available at [this link](http://nifty.stanford.edu/2014/mccown-schelling-model-segregation/).
in this simulation if someone is not satisfied , will be moved to some other random place; otherwise will remain still. satisfaction will be made for one cell if rate of those with same race at adjacent is more than `p`.
there will be a txt containing initial formation of people in given society which its name will be given to program using `-f` flag.

### Example
parameters of simulation and initial format will be given through `./outputfile -f [txt file address] -s 15 -p 50`. there must be two output file where first one is a ppm formatted image and we must print count of unsatisfied people and also map of final formation.
