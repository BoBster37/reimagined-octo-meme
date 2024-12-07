package Models;

import java.util.ArrayList;
import java.util.List;

public class Team {

	private Contractor contractor;
	private Contractor supervisor;
	private List<Person> members = new ArrayList<>();

	public Team() {
		addTeam(this);
	}

	public void setContractor(Contractor contractor) {
		if (this.contractor != contractor) {
			this.contractor = contractor;
			if (contractor != null && contractor.getTeam() != this) {
				contractor.setTeam(this);
			}
			addMember(contractor); // Добавляем подрядчика как члена команды
		}
	}

	public void setSupervisor(Contractor supervisor) {
		if (this.contractor == supervisor && this.supervisor != supervisor) {
			this.supervisor = supervisor;
			if (supervisor != null && supervisor.getTeamUnderControl() != this) {
				supervisor.setTeamUnderControl(this);
			}
		} else if (this.contractor != supervisor) {
			System.out.println("Contractor must be a member of the team before becoming a supervisor.");
		}
	}

	public Contractor getContractor() {
		return contractor;
	}

	public Contractor getSupervisor() {
		return supervisor;
	}

	public void addMember(Person member) {
		if (!members.contains(member)) {
			members.add(member);
			// Здесь можно добавить логику установки команды для конкретного типа участника
			if (member instanceof Contractor) {
				Contractor contractorMember = (Contractor) member;
				if (contractorMember.getTeam() != this) {
					contractorMember.setTeam(this);
				}
			}
		}
	}

	public void removeMember(Person member) {
		if (members.contains(member)) {
			members.remove(member);
			// Здесь можно добавить логику удаления связи с командой для конкретного типа
			// участника
			if (member instanceof Contractor) {
				Contractor contractorMember = (Contractor) member;
				if (contractorMember.getTeam() == this) {
					contractorMember.setTeam(null);
				}
			}
		}
	}

	public int getNumberOfMembers() {
		return members.size();
	}

	public List<Person> getMembers() {
		return members;
	}

	private static List<Team> extent = new ArrayList<>();

	private static void addTeam(Team team) {
		extent.add(team);
	}

	private static void removeTeam(Team team) {
		extent.remove(team);
	}
}
