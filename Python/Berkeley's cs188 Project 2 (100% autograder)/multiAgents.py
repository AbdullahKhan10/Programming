# multiAgents.py
# --------------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
#
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


import random

import util
from game import Agent, Directions  # noqa
from util import manhattanDistance  # noqa


class ReflexAgent(Agent):
    """
      A reflex agent chooses an action at each choice point by examining
      its alternatives via a state evaluation function.

      The code below is provided as a guide.  You are welcome to change
      it in any way you see fit, so long as you don't touch our method
      headers.
    """

    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {North, South, West, East, Stop}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices)  # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()
        newFood = successorGameState.getFood()
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

        "*** YOUR CODE HERE ***"
        distanceGhost = min(manhattanDistance(newPos, ghost.configuration.pos) for ghost in newGhostStates) #gets the min distance from the new pacman position to the nearest ghost
        newFood = newFood.asList() #gets all the food locations as a list
        nearestFood = min(manhattanDistance(newPos, nextFood) for nextFood in newFood) if newFood else 0 #finds the min distance from the new pacman postion to the nearest food piece
        scaredTime = min(newScaredTimes) #gets the smallest scared time of the ghost states
        foodLeftCalc = -len(newFood) #this is a calc which enforces that if there are higher number of food locations then make this number smaller
        if scaredTime == 0: #if the ghost is not scared
            ghostCloseCalc = -10 / (distanceGhost + 1) #then make this value lower
        else:
            ghostCloseCalc = 1 / (distanceGhost + 1) #otherwise make this value bigger
        closestFoodCalc = 1 / (nearestFood + 1) #make this value smaller the closer the food is
        powerPelletsCalc = scaredTime * 5 #make this value bigger the higher the scaredTime is
        #These calc values are created as a good and bad values for each specified senario such as how close the food is and if the ghost is scared etc. and they assign values to see what the agent should do
        value = foodLeftCalc + ghostCloseCalc + closestFoodCalc + powerPelletsCalc #add all the values together to see what pac mans best move is, the higher the value the better the choice is
        return value #returns the value of the total

def scoreEvaluationFunction(currentGameState):
    """
      This default evaluation function just returns the score of the state.
      The score is the same one displayed in the Pacman GUI.

      This evaluation function is meant for use with adversarial search agents
      (not reflex agents).
    """
    return currentGameState.getScore()


class MultiAgentSearchAgent(Agent):
    """
      This class provides some common elements to all of your
      multi-agent searchers.  Any methods defined here will be available
      to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

      You *do not* need to make any changes here, but you can if you want to
      add functionality to all your adversarial search agents.  Please do not
      remove anything, however.

      Note: this is an abstract class: one that should not be instantiated.  It's
      only partially specified, and designed to be extended.  Agent (game.py)
      is another abstract class.
    """

    def __init__(self, evalFn="scoreEvaluationFunction", depth="2"):
        self.index = 0  # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)


class MinimaxAgent(MultiAgentSearchAgent):
    """
      Your minimax agent (question 2)
    """

    def getAction(self, gameState):
        """
          Returns the minimax action from the current gameState using self.depth
          and self.evaluationFunction.

          Here are some method calls that might be useful when implementing minimax.

          gameState.getLegalActions(agentIndex):
            Returns a list of legal actions for an agent
            agentIndex=0 means Pacman, ghosts are >= 1

          gameState.generateSuccessor(agentIndex, action):
            Returns the successor game state after an agent takes an action

          gameState.getNumAgents():
            Returns the total number of agents in the game
        """
        "*** YOUR CODE HERE ***"
        def terminalTest(gameState, depth): #this function determines whether the game state is in its terminal state ie. the game is won, lost
            if gameState.isWin() or gameState.isLose() or depth == self.depth: #checks if the game is won, lost, or the depth is eqaual to the self.depth
                return True #returns true if the game is in this state
            else:
                return False #returns false otherwise

        def maximizer(gameState, depth): #the maximizer function which is the adversary ie the ghosts
            if terminalTest(gameState, depth): #if the terminal test passes then returns the minimax action from the current gameState using self.evaluationFunction
                return self.evaluationFunction(gameState) #returns the minimizer action from the current gamestate
            nodeValueMax = float('-inf') #initialize the nodevalueMini to infinite since we are trying to find the maxiumum value
            for action in gameState.getLegalActions(0): #for all the legal actions in the game
                nodeValueMax = max(nodeValueMax, minimizer(gameState.generateSuccessor(0, action), depth, 1)) #make the nodeValueMax the maximum of all the minimizer values
            return nodeValueMax #return the calculated nodeValuemax value

        def minimizer(gameState, depth, ghost): #the minimizer function which is the adversary ie the ghosts
            if terminalTest(gameState, depth): #if the terminal test passes then returns the minimax action from the current gameState using self.evaluationFunction
                return self.evaluationFunction(gameState) #returns the minimizer action from the current gamestate
            nodeValueMini = float('inf') #initialize the nodevalueMini to infinite since we are trying to find the minimum value
            for action in gameState.getLegalActions(ghost): #for all the legal actions in the game
                if ghost == lastIndex: #if the ghost is the last ghost in the list of index of ghosts
                    nodeValueMini = min(nodeValueMini, maximizer(gameState.generateSuccessor(ghost, action), depth + 1)) #then make nodeValueMini the minimum of all the maximizer values
                else:
                    nodeValueMini = min(nodeValueMini, minimizer(gameState.generateSuccessor(ghost, action), depth, ghost + 1)) #then make nodeValueMini the minmum of all the actions
            return nodeValueMini #return the calculated nodeValueMini value

        ghosts = ([index for index in range(1, gameState.getNumAgents())]) #creates a list of all the indexes of the ghosts, skips the pacman agent since index of pacman = 0
        lastIndex = ghosts[-1] #gets the index of the last ghost in the list
        minimaxAction = [(legalActions, minimizer(gameState.generateSuccessor(0, legalActions), 0, 1)) for legalActions in gameState.getLegalActions(0)] #for all the legal actions of the gameState run the minimizer function with an intial depth of 0 and number of ghosts as 1 to get a list of actions
        minimaxAction.sort(key=lambda k: k[1]) #sort the list according to their maxiumum values
        minimaxAction = minimaxAction[-1][0] #get the resultant action according to max action
        return minimaxAction #return the action

class AlphaBetaAgent(MultiAgentSearchAgent):
    """
      Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState):
        """
          Returns the minimax action using self.depth and self.evaluationFunction
        """
        "*** YOUR CODE HERE ***"
        util.raiseNotDefined()


class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def getAction(self, gameState):
        """
          Returns the expectimax action using self.depth and self.evaluationFunction

          All ghosts should be modeled as choosing uniformly at random from their
          legal moves.
        """
        "*** YOUR CODE HERE ***"
        maximizer = (float('-inf'), Directions.STOP) #sets maximizer to default -inf value and the default stop action
        for legalAction in gameState.getLegalActions(0): #for all the legal actions in the game state
            newPos = gameState.generateSuccessor(0, legalAction) #get all the sucessors of the new position ie legalAction
            legalActionItr = (self.Expectimax(newPos, 0, 1), legalAction) #run the expectimax function for all the legal postions
            if maximizer[0] < legalActionItr[0]: #if the particular iteration is greater than the maximizer variable containing the best action
                maximizer = (legalActionItr[0], legalActionItr[1]) #then make that iteration eqaul the new maximizer
        return maximizer[1] #return the action associated to the maximizer

    def Expectimax(self, gameState, depth, pacmanIndex): #this calculates the expectimax values of the gameState
        if  gameState.isWin() or gameState.isLose() or depth == self.depth: #check whether the gamestate is a terminal state
            return self.evaluationFunction(gameState) #since it is a terminal state return
        return self.maximize(gameState, depth) if pacmanIndex is 0 else self.averageCase(gameState, depth, pacmanIndex) #if the pacman agent index is 0 then run the maximize algorithm and if not then run the averageCase algorithm

    def maximize(self, gameState, depth): #this returns the maximum value of the gameState
        maximum = float('-inf') #initialize to -infinite
        for legalAction in gameState.getLegalActions(0): #for all the legal actions
            maximum = max(maximum, self.Expectimax(gameState.generateSuccessor(0, legalAction), depth, 1)) #run the expectimax algorithm for all the sucessors and then get the maximum
        return maximum #return the found maximum value

    def averageCase(self, gameState, depth, pacmanIndex): #this returns the average value of the gameState
        average = 0 #initilize the average to 0
        for legalAction in gameState.getLegalActions(pacmanIndex): #for all the legal actions set average to the result of the expectimax algorithm and increment the depth by one or if the pacman index is the number of agents -1 then do the expectimax algorithm without incrementing depth and put in parameter as theincrement the pacman index
            average = average + self.Expectimax(gameState.generateSuccessor(pacmanIndex, legalAction), depth + 1, 0) if pacmanIndex is gameState.getNumAgents() - 1 else average + self.Expectimax(gameState.generateSuccessor(pacmanIndex, legalAction), depth, pacmanIndex + 1)
        return average #return the average

def betterEvaluationFunction(currentGameState):
    """
      Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
      evaluation function (question 5).

      DESCRIPTION: <write something here so we know what you did>
    """
    "*** YOUR CODE HERE ***"
    util.raiseNotDefined()


# Abbreviation
better = betterEvaluationFunction
