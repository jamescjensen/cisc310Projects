import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;


public class Building {
	
	private List<Elevator> 	elevators = new ArrayList<Elevator>();
//	private Elevator 		elevator;
	private int 			floors = 100000; // Default number of floors
	 
	private Lock 			elevatorsAvaliableLock;
	private Condition 		availableCondition;
	
	public Building(int elevatorCount, int floorCount) {
		for(int i=0;i<elevatorCount;i++){
			elevators.add(new Elevator(i, this));
			new Thread(elevators.get(i)).start();
		}
		
		this.floors = floorCount;
		this.elevatorsAvaliableLock = new ReentrantLock();
		this.availableCondition = elevatorsAvaliableLock.newCondition(); // Condition tied to lock
//		this.elevator = new Elevator(0, this);
		
//		// Start elevator thread
//		new Thread(elevator).start();
	}
	
	/** Called by the person object when they want to get on the elevator
	 */
	public void getOnElevator(Person person) throws InterruptedException {
		// TODO Lock what??
		this.getElevatorsAvaliableLock().lock();
		
		try {	
			int elevatorId = -1;
			
			for(int i = 0; i < this.getElevators().size(); i++) {
				elevatorId = i;
				
				System.out.println("Elevator check: " + elevatorId);
				// Wait until the elevator is not on the same floor
				while(person.getCurrentFloor() != this.getElevators().get(i).getCurrentFloor() ||
						this.getElevators().get(i).getCurrentNumPeople() >= this.getElevators().get(i).getMaxCapacity()) { // TODO or the elevator is not going on the direction they want to go
					// Wait
					this.getAvailableCondition().await();
				}
			}
			
			System.out.println(person.getName() + " taking elevator " + this.getElevators().get(elevatorId).getId());
			
			// Put person in the elevator
			this.getElevators().get(elevatorId).insertPerson(person);
		}
		finally {
			// Release the lock
			this.getElevatorsAvaliableLock().unlock();			
		}
	}
	
	/** Executes the elevator logic
	 */
	public void service(Elevator elevator) {
		// TODO Lock on what??
		this.getElevatorsAvaliableLock().lock();
		
		try {
			// Move the elevator by 1 floor
			elevator.move();
			
			System.out.println("Elevator " + elevator.getId() + " arrived at floor " + elevator.getCurrentFloor());
			
			// Check the people that have arrived to their desired floor
			ArrayList<Person> peopleToRemove = new ArrayList<Person>();
			
			for(int i = 0; i < elevator.getPeopleInElevator().size(); i++) {
				// Get the person
				Person person = elevator.getPeopleInElevator().get(i);
				
				// If the person is in their destination floor, add to the list to remove
				if(person.getListFloor()[person.getNextFloor()] == elevator.getCurrentFloor()) {
					peopleToRemove.add(person);
				}
								
			}
			
			for(int j = 0; j < peopleToRemove.size(); j ++) {
				// Remove person
				elevator.removePerson(peopleToRemove.get(j));
				
				// Update the person's current floor
				peopleToRemove.get(j).updateFloor(elevator.getCurrentFloor());
		
				System.out.println(peopleToRemove.get(j).getName() + " arrived at floor " + peopleToRemove.get(j).getCurrentFloor());
				// TODO Now the person should sleep and continue
			}
			
			
			// TODO might not work if things happen to fast. We got: 
			// Exception in thread "Thread-0" java.lang.NullPointerException
			// Signal all waiting people that the elevator has arrived to a floor
			this.availableCondition.signalAll(); 
						
			
			// If the elevator has reached the last floor or the first floor, switch directions
			if(elevator.getCurrentFloor() == this.getFloors() || elevator.getCurrentFloor() == 0) {
				elevator.changeDirection();
			}
		}
		finally {
			// Release the lock
			this.getElevatorsAvaliableLock().unlock();
		}
	}
	
	// Getters	
	public int getFloors() { return this.floors; }
	
	public List<Elevator> getElevators() { return this.elevators; }

	public Lock getElevatorsAvaliableLock() {
		return this.elevatorsAvaliableLock;
	}

	public Condition getAvailableCondition() {
		return this.availableCondition;
	}

	// Setters
	public void setElevatorsAvaliableLock(Lock elevatorsAvaliableLock) {
		this.elevatorsAvaliableLock = elevatorsAvaliableLock;
	}

	public void setAvailableCondition(Condition availableCondition) {
		this.availableCondition = availableCondition;
	}
	
}
