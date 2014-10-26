import java.util.ArrayList;

public class Elevator implements Runnable {
	
	private static final int MAX_CAPACITY = 3;
	
	private static int nextId = 0;
	
	private Building 	building;
	private ArrayList<Person> peopleInElevator = new ArrayList<Person>(MAX_CAPACITY);
	private int 		id;
	private int 		currentFloor;
	private int 		currentNumPeople;
	private int			direction;
		
	public Elevator(int id, Building building) {
		this.id = id;
//		Elevator.nextId++;
		
		this.currentFloor = 0;
		this.currentNumPeople = 0;	
		this.building = building;
		this.direction = 1;
		}
	
	
	
//	/** Opens the door of the elevator. Lets people out and gets people in
//	 */
//	public void open() {
//		System.out.println("Elevator " + this.getId() + " arrived at floor " + this.getCurrentFloor());
//		// TODO Let people go
//		// TODO Get People in
//		// TODO Close
//	}
//	
//	
//	/** Closes the door of the elevator
//	 */
//	private void close() {
//		System.out.println("Elevator " + this.getId() + " serviced floor " + this.getCurrentFloor());
//		// TODO Move()
//	}
//	
//	/** Moves the elevator either up or down 1 floor
//	 */
//	public void move() {
//		// Go either up or down
//		// Update the current floor
//	}

	@Override  
	public void run() {
		try {
			while(true) { // TODO needs to stop when every person has gone to all of the floors they wanted.
				building.move();
				Thread.sleep(1000);
//				Building.service();
			}
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}		
	}
	
	
	public void insertPerson(Person person) {
		this.peopleInElevator.add(person);
	}
	
	public void removePerson(Person person) {
		this.peopleInElevator.remove(person);
	}
	
	// Getters and setters
	public int getId() { return this.id; }
		
	public int getCurrentFloor() { return this.currentFloor; }
	
	public int getMaxCapacity() { return Elevator.MAX_CAPACITY; }
	
	public int getDirection() {
		return this.direction;
	}
	
	public void setDirection(int direction) { this.direction = direction; }
	
	public ArrayList<Person> getPeopleInElevator() { return this.peopleInElevator; }
	
//	public Buidling getBuilding() { return this.building; }
	
	public void setCurrentFloor(int currentFloor) { this.currentFloor = currentFloor; }
	
	public int getCurrentNumPeople() { return this.currentNumPeople; }
	
	public void setCurrentNumPeople(int currentNumPeople) { this.currentNumPeople = currentNumPeople; }
	
}
