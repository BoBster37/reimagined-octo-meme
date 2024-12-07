package controllers;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import models.Project;
import models.Task;

import java.io.IOException;

public class TasksController {

    @FXML
    private GridPane tasksGridPane;

    @FXML
    private Button backButton;

    private Project project;

    public void setProject(Project project) {
        this.project = project;
        displayTasks();
    }

    private void displayTasks() {
        tasksGridPane.getChildren().clear();
        
        int column = 0;
        int row = 0;

        for (Task task : project.getTasks()) {
            VBox taskBox = new VBox(10);
            taskBox.setStyle("-fx-border-color: #ddd; -fx-padding: 15; -fx-background-color: #f9f9f9;");

            Text taskName = new Text(task.getName());
            taskName.setStyle("-fx-font-size: 18; -fx-font-weight: bold;");

            Text taskDetails = new Text(task.getDescription());
            taskDetails.setWrappingWidth(200);

            taskBox.getChildren().addAll(taskName, taskDetails);

            tasksGridPane.add(taskBox, column, row);

            column++;
            if (column == 3) {
                column = 0;
                row++;
            }
        }
    }

    @FXML
    private void handleBackButtonAction() {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/fxml/Projects.fxml"));
            Parent root = loader.load();

            ProjectsController projectsController = loader.getController();
            projectsController.setManager(project.getManager());

            Stage stage = (Stage) tasksGridPane.getScene().getWindow();
            stage.setScene(new Scene(root, stage.getWidth(), stage.getHeight()));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
