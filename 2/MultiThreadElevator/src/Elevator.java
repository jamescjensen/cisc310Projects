import java.util.ArrayList;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Elevator implements Runnable {
	
	private static final int MAX_CAPACITY = 3;
	
	private ArrayList<Person> 	peopleInElevator;
	private Building 			building;
	private int 				id;
	private int 				currentFloor;
	private int					direction;
			
	public Elevator(int id, Building building) {
		this.id = id;
		this.peopleInElevator = new ArrayList<Person>(MAX_CAPACITY);
		this.currentFloor = 0;
		this.building = building;
		this.direction = 1;
	}
	
	
	@Override  
	/** Runs the Person thread
	 */
	public void run() {

		try {
			while(true) { // TODO needs to stop when every person has gone to all of the floors they wanted.
				// Move the elevator
				this.getBuilding().service(this);
				
				// Sleep for 1 second so that people exit and enter the elevator
				Thread.sleep(2000);
				System.out.println("\t\t\t\tElevator " + this.getId() + " serviced floor " + this.getCurrentFloor());
			}
		} catch (InterruptedException ie) {
			ie.printStackTrace();
		}	
	}
	
	/** Inserts a person in the elevator
	 */
	public void insertPerson(Person person) {
		this.peopleInElevator.add(person);
	}
	
	/** Removes a person from the elevator
	 */
	public void removePerson(Person person) {
		this.peopleInElevator.remove(person);
	}
	
	/** Changes the direction of the elevator
	 */
	public void changeDirection() {
		this.setDirection(this.getDirection() * -1);
	}
	
	public void move() {
		this.setCurrentFloor(this.getCurrentFloor() + this.getDirection());
	}
	
	// Getters 
	public int getId() { return this.id; }
		
	public int getCurrentFloor() { return this.currentFloor; }
	
	public int getMaxCapacity() { return Elevator.MAX_CAPACITY; }
	
	public int getDirection() {	return this.direction; }
	
	public ArrayList<Person> getPeopleInElevator() { return this.peopleInElevator; }

	public Building getBuilding() { return this.building; }
	
	public int getCurrentNumPeople() { return this.peopleInElevator.size(); }

	
	// Setters
	
	public void setDirection(int direction) { this.direction = direction; }

	public void setCurrentFloor(int currentFloor) { this.currentFloor = currentFloor; }
	
}
