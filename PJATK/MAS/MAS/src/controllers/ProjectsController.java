package controllers;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import models.Manager;
import models.Project;

import java.io.IOException;

public class ProjectsController {

    @FXML
    private Text username;

    @FXML
    private GridPane projectsGridPane;

    private Manager manager;

    public void setManager(Manager manager) {
        this.manager = manager;
        displayProjects();
        username.setText(manager.getName() + " " + manager.getSurname()); // Установка имени пользователя
    }

    private void displayProjects() {
        projectsGridPane.getChildren().clear();

        int column = 0;
        int row = 0;

        for (Project project : manager.getProjects()) {
            VBox projectBox = new VBox(10);
            projectBox.setStyle("-fx-border-color: #ddd; -fx-padding: 15; -fx-background-color: #f9f9f9;");

            Text projectName = new Text(project.getName());
            projectName.setStyle("-fx-font-size: 18; -fx-font-weight: bold;");

            Text projectDetails = new Text(project.getDetails());
            projectDetails.setWrappingWidth(200);

            Button detailsButton = new Button("View Tasks");
            detailsButton.setOnAction(e -> openProjectTasks(project));

            projectBox.getChildren().addAll(projectName, projectDetails, detailsButton);
            projectsGridPane.add(projectBox, column, row);

            column++;
            if (column == 2) {
                column = 0;
                row++;
            }
        }
    }

    private void openProjectTasks(Project project) {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/fxml/Tasks.fxml"));
            Parent root = loader.load();

            TasksController tasksController = loader.getController();
            tasksController.setProject(project);

            Stage stage = (Stage) projectsGridPane.getScene().getWindow();
            stage.setScene(new Scene(root, stage.getWidth(), stage.getHeight()));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @FXML
    private void handleSignOut() {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/fxml/Login.fxml"));
            Parent root = loader.load();
            Stage stage = (Stage) projectsGridPane.getScene().getWindow();
            stage.setScene(new Scene(root, stage.getWidth(), stage.getHeight()));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
