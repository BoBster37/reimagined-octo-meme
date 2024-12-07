package Models;

import java.util.ArrayList;
import java.util.List;

public class Contractor extends Person {

	private List<Comment> comments = new ArrayList<>();
	private Team team;
	private Team teamUnderControl;

	public Contractor(String name, String surname, int pesel) throws Exception {
		super(name, surname, pesel);
		addContractor(this);
	}

	public void setTeam(Team team) {
		if (this.team != team) {
			this.team = team;
			if (team != null && team.getContractor() != this) {
				team.setContractor(this);
			}
		}
	}

	public void setTeamUnderControl(Team team) {
		if (this.teamUnderControl != team) {
			this.teamUnderControl = team;
			if (team != null && team.getSupervisor() != this) {
				team.setSupervisor(this);
			}
		}
	}

	public Team getTeam() {
		return team;
	}

	public Team getTeamUnderControl() {
		return teamUnderControl;
	}

	public List<Comment> getComments() {
		return comments;
	}

	public void addComment(Comment comment) {
		if (!comments.contains(comment)) {
			comments.add(comment);
			if (comment.getContractor() != this) {
				comment.setContractor(this);
			}
		}
	}

	private static List<Contractor> extent = new ArrayList<>();

	private static void addContractor(Contractor contractor) {
		extent.add(contractor);
	}

	private static void removeContractor(Contractor contractor) {
		extent.remove(contractor);
		uniquePesels.remove(contractor.getPesel()); 
	}
}
