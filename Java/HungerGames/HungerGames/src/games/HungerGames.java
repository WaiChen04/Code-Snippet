package games;

import java.util.ArrayList;



/**
 * This class contains methods to represent the Hunger Games using BSTs.
 * Moves people from input files to districts, eliminates people from the game,
 * and determines a possible winner.
 * 
 * @author Pranay Roni
 * @author Maksims Kurjanovics Kravcenko
 * @author Kal Pandit
 */
public class HungerGames {

    private ArrayList<District> districts; // all districts in Panem.
    private TreeNode game; // root of the BST. The BST contains districts that are still in the game.

    /**
     * ***** DO NOT REMOVE OR UPDATE this method *********
     * Default constructor, initializes a list of districts.
     */
    public HungerGames() {
        districts = new ArrayList<>();
        game = null;
        StdRandom.setSeed(2023);
    }

    /**
     * ***** DO NOT REMOVE OR UPDATE this method *********
     * Sets up Panem, the universe in which the Hunger Games takes place.
     * Reads districts and people from the input file.
     * 
     * @param filename will be provided by client to read from using StdIn
     */
    public void setupPanem(String filename) {
        StdIn.setFile(filename); // open the file - happens only once here
        setupDistricts(filename);
        setupPeople(filename);
    }

    /**
     * Reads the following from input file:
     * - Number of districts
     * - District ID's (insert in order of insertion)
     * Insert districts into the districts ArrayList in order of appearance.
     * 
     * @param filename will be provided by client to read from using StdIn
     */
    public void setupDistricts(String filename) {

        int count = StdIn.readInt();
        for (int i = 0; i < count; i++) {
            int ID = StdIn.readInt();
            districts.add(new District(ID));
        }
    }

    /**
     * Reads the following from input file (continues to read from the SAME input
     * file as setupDistricts()):
     * Number of people
     * Space-separated: first name, last name, birth month (1-12), age, district id,
     * effectiveness
     * Districts will be initialized to the instance variable districts
     * 
     * Persons will be added to corresponding district in districts defined by
     * districtID
     * 
     * @param filename will be provided by client to read from using StdIn
     */
    public void setupPeople(String filename) {

        int count = StdIn.readInt();
        for (int i = 0; i < count; i++) {
            String firstName = StdIn.readString();
            String lastName = StdIn.readString();
            int birthMonth = StdIn.readInt();
            int age = StdIn.readInt();
            int districtID = StdIn.readInt();
            int effectiveness = StdIn.readInt();
            Person addPerson = new Person(birthMonth, firstName, lastName, age, districtID, effectiveness);

            if (age < 18 && age >= 12) {
                addPerson.setTessera(true);
            } else {
                addPerson.setTessera(false);
            }

            for (District j : districts) {
                if (j.getDistrictID() == addPerson.getDistrictID()) {
                    if (addPerson.getBirthMonth() % 2 == 0) {
                        j.addEvenPerson(addPerson);
                    } else {
                        j.addOddPerson(addPerson);
                    }
                }
            }
        }
    }

    /**
     * Adds a district to the game BST.
     * If the district is already added, do nothing
     * 
     * @param root        the TreeNode root which we access all the added districts
     * @param newDistrict the district we wish to add
     */
    public void addDistrictToGame(TreeNode root, District newDistrict) {
        if (root == null) {
            game = new TreeNode(newDistrict, null, null);
            districts.remove(newDistrict);
        } else {
            int valueID = newDistrict.getDistrictID();
            int rootID = root.getDistrict().getDistrictID();

            if (valueID < rootID) {
                if (root.getLeft() == null) {
                    root.setLeft(new TreeNode(newDistrict, null, null));
                    districts.remove(newDistrict);
                } else {
                    addDistrictToGame(root.getLeft(), newDistrict);
                }
            } else if (valueID > rootID) {
                if (root.getRight() == null) {
                    root.setRight(new TreeNode(newDistrict, null, null));
                    districts.remove(newDistrict);
                } else {
                    addDistrictToGame(root.getRight(), newDistrict);
                }
            }
        }
    }

    /**
     * Searches for a district inside of the BST given the district id.
     * 
     * @param id the district to search
     * @return the district if found, null if not found
     */
    public District findDistrict(int id) {
        TreeNode root = game;
        while (root != null) {
            District currentDistrict = root.getDistrict();
            int currentInt = currentDistrict.getDistrictID();
            if (currentInt == id) {
                return currentDistrict;
            } else if (currentInt > id) {
                root = root.getLeft();
            } else if (currentInt < id) {
                root = root.getRight();
            }

        }

        return null; // update this line
    }

    /**
     * Selects two duelers from the tree, following these rules:
     * - One odd person and one even person should be in the pair.
     * - Dueler with Tessera (age 12-18, use tessera instance variable) must be
     * retrieved first.
     * - Find the first odd person and even person (separately) with Tessera if they
     * exist.
     * - If you can't find a person, use StdRandom.uniform(x) where x is the
     * respective
     * population size to obtain a dueler.
     * - Add odd person dueler to person1 of new DuelerPair and even person dueler
     * to
     * person2.
     * - People from the same district cannot fight against each other.
     * 
     * @return the pair of dueler retrieved from this method.
     */
    public DuelPair selectDuelers() {

        TreeNode root = game;
        DuelPair pair = new DuelPair();
        tesseraSelectOdd(root, pair);
        tesseraSelectEven(root, pair);

        if (pair.getPerson1() == null) {
            randomSelectOdd(root, pair);
        }
        if (pair.getPerson2() == null) {
            randomSelectEven(root, pair);
        }


        return pair; // update this line
    }

    private void tesseraSelectOdd(TreeNode x, DuelPair pair) {
        if (x == null)
            return;
        if (pair.getPerson1() == null) {
            District currentDistrict = x.getDistrict();
            if ((pair.getPerson2() == null) || ((pair.getPerson2() != null) && (currentDistrict.getDistrictID() != pair.getPerson2().getDistrictID()))) {
                    for (Person i : currentDistrict.getOddPopulation()) {
                        if (i.getTessera() == true) {
                            pair.setPerson1(i);
                            currentDistrict.getOddPopulation().remove(i);
                            break;
                        }
                    }
                }
            } 
        tesseraSelectOdd(x.getLeft(), pair); // recursively called with left subtree
        tesseraSelectOdd(x.getRight(), pair); // recursively called with right subtree
    }

    private void tesseraSelectEven(TreeNode x, DuelPair pair) {
        if (x == null)
            return; // reach the leaf node
        if (pair.getPerson2() == null) {
            District currentDistrict = x.getDistrict();
            if (pair.getPerson1() == null|| (pair.getPerson1() != null && (currentDistrict.getDistrictID() != pair.getPerson1().getDistrictID()))) {
                    for (Person i : currentDistrict.getEvenPopulation()) {
                        if (i.getTessera() == true) {
                            pair.setPerson2(i);
                            currentDistrict.getEvenPopulation().remove(i);
                            break;
                        }
                    }
                }
            }
        tesseraSelectEven(x.getLeft(), pair); // recursively called with left subtree
        tesseraSelectEven(x.getRight(), pair); // recursively called with right subtree
    }

    private void randomSelectOdd(TreeNode x, DuelPair pair) {
        if (x == null || pair.getPerson1() != null)
            return; // reach the leaf node
        while (pair.getPerson1() == null) {
        District currentDistrict = x.getDistrict();

            if (pair.getPerson2() == null|| (pair.getPerson2() != null && (currentDistrict.getDistrictID() != pair.getPerson2().getDistrictID()))) {
                    int pop = currentDistrict.getOddPopulation().size();
                    int randomint = StdRandom.uniform(pop);

                    Person i = currentDistrict.getOddPopulation().get(randomint);
                    pair.setPerson1(i);
                    currentDistrict.getOddPopulation().remove(i);
                    break;
                }
                break;
            } 
       randomSelectOdd(x.getLeft(), pair); // recursively called with left subtree
        randomSelectOdd(x.getRight(), pair); // recursively called with right subtree
    }

    private void randomSelectEven(TreeNode x, DuelPair pair) {
        if (x == null || pair.getPerson2() != null)
            return; // reach the leaf node
        if (pair.getPerson2() == null) {
            District currentDistrict = x.getDistrict();

            if (pair.getPerson1() == null|| (pair.getPerson1() != null && (currentDistrict.getDistrictID() != pair.getPerson1().getDistrictID()))) {
            int pop = currentDistrict.getEvenPopulation().size();
                int randomint = StdRandom.uniform(pop);
                Person i = currentDistrict.getEvenPopulation().get(randomint);
                pair.setPerson2(i);
                currentDistrict.getEvenPopulation().remove(i);
            }
        }
        randomSelectEven(x.getLeft(), pair); // recursively called with left subtree
        randomSelectEven(x.getRight(), pair); // recursively called with right subtree
    }

    /**
     * Deletes a district from the BST when they are eliminated from the game.
     * Districts are identified by id's.
     * If district does not exist, do nothing.
     * 
     * This is similar to the BST delete we have seen in class.
     * 
     * @param id the ID of the district to eliminate
     */
    public void eliminateDistrict(int id) {

        

        if(findDistrict(id) != null){
            game = delete(game, id);

    }
}

    private TreeNode deleteMin(TreeNode x) {
        if (x.getLeft() == null)
            return x.getRight();
        x.setLeft(deleteMin(x.getLeft()));
        return x;
    }

    private TreeNode delete(TreeNode x, int id) {
        if (x == null)
            return null; 
        int cmp = id - x.getDistrict().getDistrictID();
        if (cmp < 0)
            x.setLeft(delete(x.getLeft(), id));
        else if (cmp > 0)
            x.setRight(delete(x.getRight(), id));
        else { 
            if (x.getRight() == null)
                return x.getLeft();
            if (x.getLeft() == null)
                return x.getRight();
            TreeNode t = x; 
            x = min(t.getRight()); 
            x.setRight(deleteMin(t.getRight()));
            x.setLeft((t.getLeft()));
        }
        return x;
    }

    private TreeNode min(TreeNode x ){
        if(x.getLeft()== null){
            return x;
        } else{
        return min(x.getLeft());
    }
    }

    /**
     * Eliminates a dueler from a pair of duelers.
     * - Both duelers in the DuelPair argument given will duel
     * - Winner gets returned to their District
     * - Eliminate a District if it only contains a odd person population or even
     * person population
     * 
     * @param pair of persons to fight each other.
     */
    public void eliminateDueler(DuelPair pair) {
        if(pair.getPerson1() == null){
            District originalDistrict = findDistrict(pair.getPerson2().getDistrictID());
            originalDistrict.addEvenPerson(pair.getPerson2());;
        }
        if(pair.getPerson2() == null){
            District originalDistrict = findDistrict(pair.getPerson1().getDistrictID());
            originalDistrict.addOddPerson(pair.getPerson2());;
        }
        if(pair.getPerson1() != null && pair.getPerson2() != null){
            District district1 = findDistrict(pair.getPerson1().getDistrictID());
            District district2 = findDistrict(pair.getPerson2().getDistrictID());
            Person winner = pair.getPerson1().duel(pair.getPerson2());
            if(winner.getBirthMonth() % 2 == 0){
                District returnDistrict = findDistrict(winner.getDistrictID());
            returnDistrict.addEvenPerson(winner);
            } else{
                District returnDistrict = findDistrict(winner.getDistrictID());
            returnDistrict.addOddPerson(winner);
            }
            if(district1.getOddPopulation().size() == 0){
                eliminateDistrict(pair.getPerson1().getDistrictID());
            }
            if(district2.getEvenPopulation().size() == 0){
                eliminateDistrict(pair.getPerson2().getDistrictID());
            }
        }
    }

    /**
     * ***** DO NOT REMOVE OR UPDATE this method *********
     * 
     * Obtains the list of districts for the Driver.
     * 
     * @return the ArrayList of districts for selection
     */
    public ArrayList<District> getDistricts() {
        return this.districts;
    }

    /**
     * ***** DO NOT REMOVE OR UPDATE this method *********
     * 
     * Returns the root of the BST
     */
    public TreeNode getRoot() {
        return game;
    }
}
