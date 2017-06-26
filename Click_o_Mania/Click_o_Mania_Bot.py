#!/bin/python
from copy import deepcopy

#This Is Harder than I thought.... This code got about 53/80 points.
#May need to research other decision solving methods (Monte Carlo Tree)
#Am I in over my head? T__T

#The most practical next step I can think of is adding
#distance away from similar colors to the equation.
#That might take a while though...... LET"S DO IT ANYWAYS
#Done by reducing variance in relation to the center of grid

#Will be implementing a Decision Tree To Find the Best Move

#MAX_DEPTH = 5 #Maximum amount of levels to analyze in decision tree
NUM_SCORE = 0
COLOR_SCORE = 5000
BIG_SCORE =  0
SMALL_SCORE = 0
INDI_SCORE =  400
VARMIN_SCORE = 200
VARDIV_SCORE = 200

class gameState (object):
    

    def __init__ (self, rows, cols, colors, grid):
        self.rows = rows
        self.cols = cols
        self.colors = colors
        self.grid = deepcopy(grid) #Need Deep Copy to Copy List, not Reference
        self.bestMove = []
        self.possibleMoves = [] #List of Arrays [row, col]
        self.score = 0 
        self.numBlocks = 0
        self.gameOver = False        
    
    def analyzeState(self):
        #print "Analyzing State"
        #Group Blocks Together, simultaneously keeping score.
        #For each group, puts one of the members as a possible move.
        checkedBlocks = []
        currentColors = {} #Contains Colors and All Blocks of that Color
        numColors = {} #Contains The number of blocks of each color
        self.numBlocks = 0
        
        for r in xrange(self.rows):
          for c in xrange(self.cols):
            if self.grid[r][c] != '-':
              self.numBlocks += 1
              if self.grid[r][c] not in currentColors: 
                currentColors[self.grid[r][c]] = [0]
              currentColors[self.grid[r][c]][0] += 1
              currentColors[self.grid[r][c]].append([r, c])
              
              if ([r, c] not in checkedBlocks):
                [groupSize, groupMembers] = self.groupBlocks(r, c)
                checkedBlocks.extend(groupMembers)
                if groupSize > 5:
                  self.possibleMoves.append([r, c])
                  self.score += BIG_SCORE * groupSize #Can Be Tweaked
                elif groupSize > 1:
                  self.possibleMoves.append([r, c])
                  self.score += SMALL_SCORE * groupSize #Can Be Tweaked
                else:
                  self.score -= INDI_SCORE #Can Be Tweaked
        
        #Updating Score based on other factors
        #print "Number of Colors", len(currentColors)
        #print "Number of Blocks", self.numBlocks        
        self.score -= (len(currentColors) * COLOR_SCORE) #Can Be Tweaked
        self.score -= (self.numBlocks * NUM_SCORE) # Can Be Tweaked
        for c in currentColors.keys():
          if currentColors[c][0] == 1:
            #print "Only one of ", c
            self.score -= 10000000 #Lose if one Color Has only One Block
            self.gameOver = True
            return
          else:
            numColors[c] = currentColors[c].pop(0)
            
        #Adding Special Scoring Method For Minimizing Variance Between
        #Same-Colored Blocks
        #print currentColors
        for c in currentColors.keys():
          meanx = sum(point[0] for point in currentColors[c]) / len(currentColors[c])
          meany = sum(point[1] for point in currentColors[c]) / len(currentColors[c])
          tempx = sum(pow((point[0] - meanx), 2) for point in currentColors[c])
          tempy = sum(pow((point[1] - meany), 2) for point in currentColors[c])
          varx = tempx / len(currentColors[c])
          vary = tempy / len(currentColors[c])
          var = pow(varx, 2) + pow(vary, 2)
          self.score -= (var * VARMIN_SCORE) * (VARDIV_SCORE/numColors[c])
        
          
        #Check if No Possible Moves
        if len(self.possibleMoves) == 0:
          #print "Game Over Found"          
          for col in xrange(self.cols):
            if self.grid[self.rows - 1][col] == '-': #WTF?! Why was this '0'?!!!
              winner = True
            else:
              winner = False
              break
          if winner:
            self.score += 10000000 #Winning Game
          else:
            self.score -= 10000000 #Losing Game
          self.gameOver = True 
        else:
          self.gameOver = False
          
        return
        
    
    def newGrid(self, click_row, click_col):
        newState = gameState(self.rows, self.cols, self.colors, self.grid)
        
        #Find Spot to Delete and Delete Attached Blocks of Same Color
        [temp, groupMembers] = newState.groupBlocks(click_row, click_col)
        for blocks in groupMembers:
          newState.grid[blocks[0]][blocks[1]] = '-'
        
        #Starting from the bottom,
        #Moves blocks down if there's an empty space under it
        for c in xrange(newState.cols):
          for r in range(newState.rows - 1, -1, -1):          
            if newState.grid[r][c] == '-':
              rowDown = r - 1 #Finds Nearest Block Above to move Down
              while rowDown >= 0:
                if newState.grid[rowDown][c] != '-':
                  break
                rowDown -= 1              
              if rowDown < 0:
                break #Move to next column if no more blocks above
              else:  
                newState.grid[r][c] = newState.grid[rowDown][c]
                newState.grid[rowDown][c] = '-'
        
        #Move Columns Left if a Column is Empty
        for c in xrange(newState.cols - 1):
          if newState.grid[newState.rows - 1][c] == '-':
            colMove = c + 1
            while colMove < newState.cols:
              if newState.grid[newState.rows - 1][colMove] != '-':
                break
              colMove += 1
            if colMove >= newState.cols:
              break #No More Columns to Move
            else:
              for r in xrange(newState.rows):
              #Moves all blocks in colmove to current column.
                newState.grid[r][c] = newState.grid[r][colMove]
                newState.grid[r][colMove] = '-'        
                
        return newState
    
    def groupBlocks(self, r, c):
      #print "Grouping Blocks:", r, c
      output = []
      groupMembers = []
      groupMembers.append([r, c])
      colorCheck = self.grid[r][c]
      needToCheck = [] #Queue
      finished = False;
      
      while not(finished):
        #Checks in All Directions
        if (r + 1) < self.rows:
          if self.grid[r + 1][c] == colorCheck:
            if [(r + 1), c] not in groupMembers:
              groupMembers.append([(r + 1), c])
              needToCheck.append([(r + 1), c])
        if (c + 1) < self.cols:
          if self.grid[r][c + 1] == colorCheck:
            if [r, (c + 1)] not in groupMembers:
              groupMembers.append([r, (c + 1)])
              needToCheck.append([r, (c + 1)])
        if (r - 1) >= 0:
          if self.grid[r - 1][c] == colorCheck:
            if [(r - 1), c] not in groupMembers:
              groupMembers.append([(r - 1), c])
              needToCheck.append([(r - 1), c])
        if (c - 1) >= 0:
          if self.grid[r][c - 1] == colorCheck:
            if [r, (c - 1)] not in groupMembers:
              groupMembers.append([r, (c - 1)])
              needToCheck.append([r, (c - 1)])
              
        if len(needToCheck) != 0:
          [r, c] = needToCheck.pop(0)
          #print "Now Checking:", r, c
        else:
          finished = True         
      
      output.append(len(groupMembers)) #Size of Group
      output.append(groupMembers)
      
      return output

def decisionTree(depth, state = gameState):
    #print "Analyzing State in", depth
    
    state.analyzeState(); #Finds all possible moves and state's score.
    
    #print state.numBlocks
    #Changing Max Depth to make Program more Efficient with less blocks
    if state.numBlocks < 30:
      MAX_DEPTH = 5    
    elif state.numBlocks < 50:
      MAX_DEPTH = 4
    elif state.numBlocks < 100:
      MAX_DEPTH = 3
    else:
      MAX_DEPTH = 2
      
    if (state.gameOver) or (depth == MAX_DEPTH):
        return state
    
    possibleStates = []
    scores = []    
    
    for move in state.possibleMoves:
        #Goes through all possible moves 
        #print "Checking Move: ", move[0], move[1]
        newState = state.newGrid(move[0], move[1])      
        newState = decisionTree(depth + 1, newState)
        possibleStates.append(newState)
        scores.append(newState.score)
        #break #For Testing
        
    #print scores
    maxScore = max(scores) #Finds Best Possible Score 
    #print "Max Score is", maxScore
    maxIndex = scores.index(maxScore)  
    state.bestMove = state.possibleMoves[maxIndex] #Best Move
    #print "Best Move is", state.bestMove
    state.score = maxScore #Updates current state's score
    
    return state
    
    
def nextMove(rows, cols, colors, grid):    
    currentState = gameState(rows, cols, colors, grid)
    analyzedState = decisionTree(0, currentState) #Finds the best move
    print analyzedState.bestMove[0], analyzedState.bestMove[1]
    return    
    
if __name__ == '__main__':
    rows,cols,k = [ int(i) for i in raw_input().strip().split() ] 
    grid = [[i for i in str(raw_input().strip())] for _ in range(rows)] 
    nextMove(rows, cols, k, grid)