package Models;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public abstract class Person {

	protected String name;
	protected String surname;
	protected String email;
	protected String password;
	protected String phoneNumber;
	protected int pesel; // unique
	protected static Set<Integer> uniquePesels = new HashSet<>();

	public Person(String name, String surname, int pesel) throws Exception {
		this.name = name;
		this.surname = surname;
		setPesel(pesel);
		addPerson(this);
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getSurname() {
		return surname;
	}

	public void setSurname(String surname) {
		this.surname = surname;
	}

	public int getPesel() {
		return pesel;
	}

	public void setPesel(int pesel) throws Exception {
		if (!isPeselUnique(pesel)) {
			throw new Exception("Pesel must be unique");
		}
		if (this.pesel != 0) {
			uniquePesels.remove(this.pesel);
		}
		this.pesel = pesel;
		uniquePesels.add(pesel);
	}

	private boolean isPeselUnique(int pesel) {
		return uniquePesels.add(pesel);
	}

	public static void removePerson(Person person) {
		extent.remove(person);
		uniquePesels.remove(person.getPesel());
	}

	private static List<Person> extent = new ArrayList<>();

	public static void addPerson(Person person) {
		extent.add(person);
	}

	public static void printUniquePesels() {
		System.out.println("Unique Pesels: " + uniquePesels);
	}
}
