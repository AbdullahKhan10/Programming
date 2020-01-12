# search.py
# ---------
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


"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""

import util

class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        util.raiseNotDefined()

    def isGoalState(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getSuccessors(self, state):
        """
          state: Search state

        For a given state, this should return a list of triples, (successor,
        action, stepCost), where 'successor' is a successor to the current
        state, 'action' is the action required to get there, and 'stepCost' is
        the incremental cost of expanding to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    return  [s, s, w, s, w, w, s, w]

def depthFirstSearch(problem):
    """
    Search the deepest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print("Start:", problem.getStartState())
    print("Is the start a goal?", problem.isGoalState(problem.getStartState()))
    print("Start's successors:", problem.getSuccessors(problem.getStartState()))
    """
    "*** YOUR CODE HERE ***"
    start_state = problem.getStartState() #set start_state to the start state of the problem
    stack = util.Stack() #creates a variable stack which is an implemented stack
    stack.push([start_state, [], 0]) #push the start state into the stack in this form (state, action, cost)
    discovered = [] #creates and empty list which will contain all the nodes that are discovered
    while not stack.isEmpty(): #iterates till the stack is empty
        node, path, cost = stack.pop() #pop the top of the stack and seperated it in to node, path, cost
        if problem.isGoalState(node): #if the node is the goal state then return the path
            return path
        if node not in discovered: #if the node is not in discovered, discover it
            discovered.append(node) #add it to discovered
            for successor, action, stepCost in problem.getSuccessors(node): #do the following for all the successors
                if successor not in discovered: #if the successor is not discovered
                    next_path = path + [action] #make next_path the action of the successor
                    successor_node = [successor, next_path, stepCost] #create a variable for the successor
                    stack.push(successor_node) #push the successor on to the stack
    return [] #return an empty list if you cannot DFS
    util.raiseNotDefined()

def breadthFirstSearch(problem):
    """Search the shallowest nodes in the search tree first."""
    "*** YOUR CODE HERE ***"
    start_state = problem.getStartState() #set start_state to the start state of the problem
    queue = util.Queue()  #creates a variable queue which is an implemented Queue
    queue.push([start_state, [], 0]) #enqueue the start state into the queue in this form (state, action, cost)
    discovered = [] #creates and empty list which will contain all the nodes that are discovered
    while not queue.isEmpty(): #iterates till the stack is empty
        node, path, cost = queue.pop() #dequeue the top and seperated it in to node, path, cost
        if problem.isGoalState(node): #if the node is the goal state then return the path
            return path
        if node not in discovered: #if the node is not in discovered, discover it
            discovered.append(node) #add it to discovered
            for successor, action, stepCost in problem.getSuccessors(node): #do the following for all the successors
                if successor not in discovered: #if the successor is not discovered
                    next_path = path + [action] #make next_path the action of the successor
                    successor_node = [successor, next_path, stepCost] #create a variable for the successor
                    queue.push(successor_node) #enqueue the successor
    return [] #return an empty list if you cannot BFS
    util.raiseNotDefined()

def uniformCostSearch(problem):
    """Search the node of least total cost first."""
    "*** YOUR CODE HERE ***"
    start_state = problem.getStartState() #set start_state to the start state of the problem
    queue = util.PriorityQueue() #creates a variable queue which is an implemented as a Priority Queue
    queue.push([start_state, [], 0], 0) #enqueue the start state into the queue in this form (state, action, cost)
    discovered = [] #creates and empty list which will contain all the nodes that are discovered
    while not queue.isEmpty(): #iterates till the stack is empty
        node, path, cost = queue.pop() #dequeue the top and seperated it in to node, path, cost
        if problem.isGoalState(node): #if the node is the goal state then return the path
            return path
        if node not in discovered: #if the node is not in discovered, discover it
            discovered.append(node) #add it to discovered
            for successor, action, stepCost in problem.getSuccessors(node): #do the following for all the successors
                if successor not in discovered: #if the successor is not discovered
                    next_cost = cost + stepCost #make next_cost the step cost of the successor
                    next_path = path + [action] #make next_path the action of the successor
                    successor_node = [successor, next_path, next_cost] #create a variable for the successor
                    queue.push(successor_node, next_cost) #enqueue the successor
    return [] #return an empty list if you cannot uniformCostSearch
    util.raiseNotDefined()

def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0

def aStarSearch(problem, heuristic=nullHeuristic):
    """Search the node that has the lowest combined cost and heuristic first."""
    "*** YOUR CODE HERE ***"
    start_state = problem.getStartState() #set start_state to the start state of the problem
    queue = util.PriorityQueue() #creates a variable queue which is an implemented as a Priority Queue
    queue.push([start_state, [], 0], 0) #enqueue the start state into the queue in this form (state, action, cost)
    discovered = [] #creates and empty list which will contain all the nodes that are discovered
    while not queue.isEmpty(): #iterates till the stack is empty
        node, path, cost = queue.pop() #dequeue the top and seperated it in to node, path, cost
        if problem.isGoalState(node): #if the node is the goal state then return the path
            return path
        if node not in discovered: #if the node is not in discovered, discover it
            discovered.append(node) #add it to discovered
            for successor, action, stepCost in problem.getSuccessors(node): #do the following for all the successors
                if successor not in discovered: #if the successor is not discovered
                    next_cost = cost + stepCost #make next_cost the step cost of the successor
                    next_path = path + [action] #make next_path the action of the successor
                    successor_node = [successor, next_path, next_cost] #create a variable for the successor
                    queue.push(successor_node, next_cost + heuristic(successor, problem)) #enqueue the successor and add heuristic to the next_cost
    return []  #return an empty list if you cannot aStarSearch
    util.raiseNotDefined()


# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
