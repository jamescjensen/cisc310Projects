import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;


public class Building {
	
//	private List<Elevator> elevators = new ArrayList<Elevator>();
	private Elevator el;
	private int f = 100000; // Number of floors
	 
	private Lock elevatorsAvaliableLock;
	
	private Condition availableCondition;
	

	public Building(int e, int f) {
//		for(int i=0;i<e;i++){
//			elevators.add(new Elevator(i));
//			new Thread(elevators.get(i)).start();
//		}
		
		this.el = new Elevator(0, this);
		
		new Thread(el).start();
		setF(f);
		
		this.elevatorsAvaliableLock = new ReentrantLock();
		this.availableCondition = elevatorsAvaliableLock.newCondition(); // Condition tied to lock
	}

	public void getOnElevator(Person person) throws InterruptedException {
		this.elevatorsAvaliableLock.lock();
		
		try {
////			while(true) {
////				for(Elevator elevator:elevators) {
//				
//					while(person.getCurrentFloor() != elevator.getCurrentFloor() && elevator.getCurrentNumPeople() >= elevator.getMaxCapacity()) {
//						this.availableCondition.await();
//					}
//					
////					break;
////				}
//					System.out.println(person.getName() + " taking elevator ");
//					
////					break;
//				
//			}
			
			
			
			while(person.getCurrentFloor() != el.getCurrentFloor() && el.getCurrentNumPeople() < el.getMaxCapacity()) {
				this.availableCondition.await();
			}
			
			System.out.println(person.getName() + " taking elevator " + el.getId());
			el.insertPerson(person);
			person.setStatus(person.getInElevator());
			el.setCurrentNumPeople(el.getCurrentNumPeople() + 1);
			

		}
		finally {
			this.elevatorsAvaliableLock.unlock();

			
		}
	}
	
	
	public void move() {
		this.elevatorsAvaliableLock.lock();
		
		try {
			el.setCurrentFloor(el.getCurrentFloor() + el.getDirection());
			
			
			System.out.println("Current floor: " + el.getCurrentFloor());
			
			this.availableCondition.signalAll();
			
//			System.out.println("Size before loop: " + el.getPeopleInElevator().size());
			
			ArrayList<Person> peopleToRemove = new ArrayList<Person>();
			
			for(int i = 0; i < el.getPeopleInElevator().size(); i++) {
//				System.out.println("Size during loop: " + el.getPeopleInElevator().size());
//				System.out.println("Loop index: " + i);
				Person p = el.getPeopleInElevator().get(i);
				
				if(p.getListFloor()[p.getNextFloor()] == el.getCurrentFloor()) {
					peopleToRemove.add(p);
//					el.removePerson(p);
				}
								
			}
			
			for(int j = 0; j < peopleToRemove.size(); j ++) {
				el.removePerson(peopleToRemove.get(j));
				peopleToRemove.get(j).setCurrentFloor(el.getCurrentFloor());
				peopleToRemove.get(j).setNextFloor(peopleToRemove.get(j).getNextFloor() + 1);
				
				System.out.println(peopleToRemove.get(j).getName() + " arrived on floor " + peopleToRemove.get(j).getCurrentFloor());
				
//				System.out.println(peopleToRemove.get(j).getCurrentFloor() == peopleToRemove.get(j).getListFloor()[peopleToRemove.get(j).getNextFloor() - 1]);
//				Thread.sleep(p.getWaitTime());	
			}
			
			
			
			
			if(el.getCurrentFloor() == this.getF() || el.getCurrentFloor() == 0) {
				el.setDirection(el.getDirection() * -1);
			}
		}
		finally {
			this.elevatorsAvaliableLock.unlock();
		}
	}
	
	public int getF(){
		return this.f;
	}
	
	public void setF(int f){
		this.f = f;
	}

}
