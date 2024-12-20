package Models;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.List;

import Models.Contractor;
import Models.Team;

public class Main {
	public static void main(String[] args) throws Exception {

		// {SUBSET} CONTRACTOR - TEAM
		System.out.println("{SUBSET}");

		Team team = new Team();

		Contractor contractor = new Contractor("bLABLA", "bLABLA", 124312);
		team.setSupervisor(contractor);

		team.setContractor(contractor);
		System.out.println("Contractor is member of team: " + (team.getContractor() == contractor));
		System.out.println("Contractor is supervisor of team: " + (team.getSupervisor() == contractor));

		team.setSupervisor(contractor);

		System.out.println("Contractor is member of team: " + (team.getContractor() == contractor));
		System.out.println("Contractor is supervisor of team: " + (contractor.getTeamUnderControl() == team));

		// {BAG} MATERIAL - PROJECT
		System.out.println();
		System.out.println("{BAG}");

		// Создаем объект Material
		Material material1 = new Material("Cement",10,"L");
		System.out.println(material1);


		// Создаем объект Project
		Project project1 = new Project();
		project1.setName("Building A");

		// Создаем первый заказ Cement для Building A
		ProjectMaterial pm1 = new ProjectMaterial(LocalDate.of(2023, 8, 1));
		pm1.setMaterial(material1);
		pm1.setProject(project1);

		// Создаем второй заказ Cement для Building A
		ProjectMaterial pm2 = new ProjectMaterial(LocalDate.of(2023, 8, 15));
		pm2.setMaterial(material1);
		pm2.setProject(project1);

		// Проверка наличия заказов
		System.out.println("Project " + project1.getName() + " materials:");
		for (ProjectMaterial pm : project1.getMaterials()) {
			System.out.println("- " + pm.getMaterial().getName() + " (Ordered on: " + pm.getOrderDate() + ")");
		}

		System.out.println("Material " + material1.getName() + " projects:");
		for (ProjectMaterial pm : material1.getOrders()) {
			System.out.println("- " + pm.getProject().getName() + " (Ordered on: " + pm.getOrderDate() + ")");
		}

		// {COMPOSITION} REPORT - CLIENT
		System.out.println();
		System.out.println("{COMPOSITION}");

		// Создаем клиента
		Client client = new Client("bLABLA", "bLABLA", 1243122);
		client.setName("Jeorge Bush");

		// Создаем проект
		Project project = new Project();
		project.setName("Project A");

		// Создаем отчет и связываем его с проектом и клиентом
		Report report1 = Report.createReport(client, "Report 1", "Content of Report 1", LocalDateTime.now());
		report1.setProject(project); // Связываем отчет с проектом

		// Создаем еще один отчет
		Report report2 = Report.createReport(client, "Report 2", "Content of Report 2", LocalDateTime.now());
		report2.setProject(project); // Связываем отчет с проектом

		// Проверка связи: Вывод всех отчетов проекта
		System.out.println("Project: " + project.getName());
		System.out.println("Reports associated with the project:");
		for (Report report : project.getReports()) {
			System.out.println("- " + report.getName() + ": " + report.getContent());
		}

		// Проверка связи: Вывод всех отчетов клиента
		System.out.println("\nClient: " + client.getName());
		System.out.println("Reports associated with the client:");
		for (Report report : client.getReports()) {
			System.out.println("- " + report.getName() + ": " + report.getContent());
		}

		// {UNIQUE} PERSON
		System.out.println();
		System.out.println("{UNIQUE}");

		// Создание объектов Client и Contractor с уникальными pesel
		Client client1 = new Client("Alice", "Brown", 123456789);
		Contractor contractor1 = new Contractor("Bob", "Green", 987654321);

		// Попытка создать Contractor с уже существующим pesel
		// Contractor contractor2 = new Contractor("Charlie", "White", 123456789); //
		// Это вызовет исключение
		
        
        Contractor contractor2 = new Contractor("Jane", "White", 020302103);
    
        
        Manager manager = new Manager("Alice",null,1231410);
             

        // Создаем команду
        Team team2 = new Team();

        // Назначаем подрядчика и супервизора
        team2.setContractor(contractor1);
        team2.setSupervisor(contractor1);  // contractor1 становится супервизором

        // Добавляем остальных участников в команду
        team2.addMember(manager);
        team2.addMember(client);

        // Выводим список участников
        List<Person> members = team2.getMembers();
        System.out.println("Members of the team:");
        for (Person member : members) {
            System.out.println(member.getName());
        }

        // Проверяем количество участников
        System.out.println("Number of members in the team: " + team2.getNumberOfMembers());

        // Проверяем связи
        System.out.println("Supervisor: " + team2.getSupervisor().getName());
        System.out.println("Contractor: " + team2.getContractor().getName());
		

	}
}
