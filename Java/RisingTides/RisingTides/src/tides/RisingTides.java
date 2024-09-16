package tides;

import java.util.*;

/**
 * This class contains methods that provide information about select terrains 
 * using 2D arrays. Uses floodfill to flood given maps and uses that 
 * information to understand the potential impacts. 
 * Instance Variables:
 *  - a double array for all the heights for each cell
 *  - a GridLocation array for the sources of water on empty terrain 
 * 
 * @author Original Creator Keith Scharz (NIFTY STANFORD) 
 * @author Vian Miranda (Rutgers University)
 */
public class RisingTides {

    // Instance variables
    private double[][] terrain;     // an array for all the heights for each cell
    private GridLocation[] sources; // an array for the sources of water on empty terrain 

    /**
     * DO NOT EDIT!
     * Constructor for RisingTides.
     * @param terrain passes in the selected terrain 
     */
    public RisingTides(Terrain terrain) {
        this.terrain = terrain.heights;
        this.sources = terrain.sources;
    }

    /**
     * Find the lowest and highest point of the terrain and output it.
     * 
     * @return double[][], with index 0 and index 1 being the lowest and 
     * highest points of the terrain, respectively
     */
    public double[] elevationExtrema() {
        double[] elevationExtrema = new double[2];

        double highest = terrain[0][0];
        double lowest = terrain[0][0];

        for(int i=0; i < terrain.length; i++){
            for(int j=0; j< terrain[i].length; j++){
                 if (terrain[i][j] >  highest){
                    highest = terrain[i][j];
                 }
                if (terrain[i][j] <  lowest){
                    lowest = terrain[i][j];
                 }                
            }
        }
        elevationExtrema[0] = lowest;
        elevationExtrema[1] = highest;        
        return elevationExtrema; // substitute this line. It is provided so that the code compiles.
    }

    /**
     * Implement the floodfill algorithm using the provided terrain and sources.
     * 
     * All water originates from the source GridLocation. If the height of the 
     * water is greater than that of the neighboring terrain, flood the cells. 
     * Repeat iteratively till the neighboring terrain is higher than the water 
     * height.
     * 
     * 
     * @param height of the water
     * @return boolean[][], where flooded cells are true, otherwise false
     */
    public boolean[][] floodedRegionsIn(double height) {
        boolean[][] resultingArray = new boolean[terrain.length][terrain[0].length];
        ArrayList<GridLocation> arrayList = new ArrayList<GridLocation>(); 
;
        
for (GridLocation i : sources) {
    arrayList.add(i);
    resultingArray[i.row][i.col] = true;
}

        while(arrayList.isEmpty() == false){
           

            for(int i  = 0; i <1;i++){
            if(arrayList.get(0).row + 1 < terrain.length && !resultingArray[arrayList.get(0).row + 1][arrayList.get(0).col]){
                if(terrain[arrayList.get(0).row + 1][arrayList.get(0).col] <= height){
                    GridLocation G = new GridLocation(arrayList.get(0).row + 1, arrayList.get(0).col);
                    resultingArray[arrayList.get(0).row + 1][arrayList.get(0).col] = true;
                    arrayList.add(G);

                    }
                }
            }
            
            for(int i  = 0; i <1;i++){
            if(arrayList.get(0).row - 1 >= 0  && !resultingArray[arrayList.get(0).row -1][arrayList.get(0).col]){
                if(terrain[arrayList.get(0).row - 1][arrayList.get(0).col] <= height){
                     resultingArray[arrayList.get(0).row - 1][arrayList.get(0).col] = true;
                    GridLocation G = new GridLocation(arrayList.get(0).row - 1, arrayList.get(0).col);
                    arrayList.add(G);

                    }
                }

            }
            for(int i  = 0; i <1;i++){
            if(arrayList.get(0).col +1 < terrain[0].length  && !resultingArray[arrayList.get(0).row][arrayList.get(0).col + 1]){
                if(terrain[arrayList.get(0).row][arrayList.get(0).col +1] <= height){
                     resultingArray[arrayList.get(0).row][arrayList.get(0).col + 1] = true;
                    GridLocation G = new GridLocation(arrayList.get(0).row, arrayList.get(0).col +1);
                    arrayList.add(G);

                    }
                }

            }
            for(int i  = 0; i <1;i++){
            if(arrayList.get(0).col - 1 >= 0 && !resultingArray[arrayList.get(0).row][arrayList.get(0).col - 1]){
                if(terrain[arrayList.get(0).row][arrayList.get(0).col - 1] <= height){
                    resultingArray[arrayList.get(0).row][arrayList.get(0).col- 1] = true;
                    GridLocation G = new GridLocation(arrayList.get(0).row, arrayList.get(0).col - 1);
                    arrayList.add(G);

                    }
                }
            }
                                arrayList.remove(0);

        }
                        for(int i=0; i < resultingArray.length; i++){
            for(int j=0; j< resultingArray[i].length; j++){
                if(resultingArray[i][j] != true ){
                resultingArray[i][j] = false;
            }
            }
        }


        
        /* WRITE YOUR CODE BELOW */
        return resultingArray; // substitute this line. It is provided so that the code compiles.
    }

    /**
     * Checks if a given cell is flooded at a certain water height.
     * 
     * @param height of the water
     * @param cell location 
     * @return boolean, true if cell is flooded, otherwise false
     */
    public boolean isFlooded(double height, GridLocation cell) {
        boolean[][] isFlooded = floodedRegionsIn(height);

        /* WRITE YOUR CODE BELOW */
        return isFlooded[cell.row][cell.col]; // substitute this line. It is provided so that the code compiles.
    }

    /**
     * Given the water height and a GridLocation find the difference between 
     * the chosen cells height and the water height.
     * 
     * If the return value is negative, the Driver will display "meters below"
     * If the return value is positive, the Driver will display "meters above"
     * The value displayed will be positive.
     * 
     * @param height of the water
     * @param cell location
     * @return double, representing how high/deep a cell is above/below water
     */
    public double heightAboveWater(double height, GridLocation cell) {
         double dif = terrain[cell.row][cell.col] - height;
        
        /* WRITE YOUR CODE BELOW */
        return dif; // substitute this line. It is provided so that the code compiles.
    }

    /**
     * Total land available (not underwater) given a certain water height.
     * 
     * @param height of the water
     * @return int, representing every cell above water
     */
    public int totalVisibleLand(double height) {

        boolean[][] isFlooded = floodedRegionsIn(height);
        int count = 0;
        for(int i = 0 ; i <terrain.length ; i++){
            for(int j = 0; j < terrain[i].length ; j++ ){
                if(isFlooded[i][j] == false){
                    count++;
                }
            }

        }
        
        /* WRITE YOUR CODE BELOW */
        return count; // substitute this line. It is provided so that the code compiles.
    } 


    /**
     * Given 2 heights, find the difference in land available at each height. 
     * 
     * If the return value is negative, the Driver will display "Will gain"
     * If the return value is positive, the Driver will display "Will lose"
     * The value displayed will be positive.
     * 
     * @param height of the water
     * @param newHeight the future height of the water
     * @return int, representing the amount of land lost or gained
     */
    public int landLost(double height, double newHeight) {
        int landLost = totalVisibleLand(height) - totalVisibleLand(newHeight);
        

        return landLost; // substitute this line. It is provided so that the code compiles.
    }

    /**
     * Count the total number of islands on the flooded terrain.
     * 
     * Parts of the terrain are considered "islands" if they are completely 
     * surround by water in all 8-directions. Should there be a direction (ie. 
     * left corner) where a certain piece of land is connected to another 
     * landmass, this should be considered as one island. A better example 
     * would be if there were two landmasses connected by one cell. Although 
     * seemingly two islands, after further inspection it should be realized 
     * this is one single island. Only if this connection were to be removed 
     * (height of water increased) should these two landmasses be considered 
     * two separate islands.
     * 
     * @param height of the water
     * @return int, representing the total number of islands
     */

     public int numOfIslands(double height) {

        boolean[][] isFlooded = floodedRegionsIn(height);

        GridLocation[] unionArray = new GridLocation[terrain.length * terrain[0].length];

        int l = 0;

for (int row = 0; row < terrain.length; row++) {
    for (int col = 0; col < terrain[0].length; col++) {
        
        unionArray[l] = new GridLocation(row, col);
        l++;
    }
}
int count = 0;

        WeightedQuickUnionUF wquf = new WeightedQuickUnionUF(terrain.length, terrain[0].length);




            for(int j = 0; j<unionArray.length -1  ; j++){
                if(isFlooded[unionArray[j].row][unionArray[j].col] == false){
                    if(unionArray[j].row + 1 < terrain.length){
                        if(isFlooded[unionArray[j].row + 1][(unionArray[j].col)] == false){
                        wquf.union(unionArray[j], unionArray[j+terrain[0].length]);
                        }
                    }
                    if(unionArray[j].row - 1 >= 0){
                        if(isFlooded[unionArray[j].row - 1][unionArray[j].col] == false){
                            wquf.union(unionArray[j], unionArray[j-terrain[0].length]);
                        } 
                    }
                    if(unionArray[j].col - 1 >= 0){
                        if(isFlooded[unionArray[j].row][unionArray[j].col - 1] == false){
                            wquf.union(unionArray[j], unionArray[j-1]);
                        }
                    }
                    if(unionArray[j].col+1 < terrain.length){
                        if(isFlooded[unionArray[j].row][unionArray[j].col+1] == false){
                            wquf.union(unionArray[j], unionArray[j+1]);
                        }
                    } 
                    if(unionArray[j].row - 1 >= 0 && unionArray[j].col - 1 >= 0){
                        if(isFlooded[unionArray[j].row - 1][unionArray[j].col - 1] == false){
                            wquf.union(unionArray[j], unionArray[j-terrain[0].length - 1]);
                        }
                    }
                    if((unionArray[j].row)+1 < terrain.length && (unionArray[j].col)-1 >= 0){
                        if(isFlooded[(unionArray[j].row) +1][(unionArray[j].col)-1] == false){
                            wquf.union(unionArray[j], unionArray[j+terrain[0].length - 1]);
                        }
                    }
                    if((unionArray[j].row) -1 >= 0 && (unionArray[j].col)+1 < terrain[0].length){
                        if(isFlooded[(unionArray[j].row) -1][(unionArray[j].col)+1] == false){
                            wquf.union(unionArray[j], unionArray[j-terrain[0].length + 1]);
                        }
                    }
                    if((unionArray[j].row) +1 < terrain.length && (unionArray[j].col)+1 < terrain[0].length){
                        if(isFlooded[(unionArray[j].row) +1][(unionArray[j].col)+1] == false){
                            wquf.union(unionArray[j], unionArray[j+terrain[0].length + 1]);
                        }
                     }
                }

            } 


        for (int j = 0; j < unionArray.length; j++) {
            if (!isFlooded[unionArray[j].row][unionArray[j].col] && wquf.find(unionArray[j]).equals(unionArray[j])) {
                count++;
            }
                        }
          
        
        return count;
                }

            }




