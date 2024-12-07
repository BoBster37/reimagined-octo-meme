package controllers;

import javafx.fxml.FXML;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.stage.Stage;
import models.Manager;
import javafx.scene.Scene;
import javafx.fxml.FXMLLoader;
import java.io.IOException;
import javafx.scene.Parent;

public class LoginController {

    @FXML
    private TextField emailField;

    @FXML
    private PasswordField passwordField;

    @FXML
    private void handleLoginButtonAction() {
        String email = emailField.getText();
        String password = passwordField.getText();

        Manager loggedInManager = getLoggedInManager(email, password);
        if (loggedInManager != null) {
            try {
                FXMLLoader loader = new FXMLLoader(getClass().getResource("/fxml/Projects.fxml"));
                Parent root = loader.load();

                // Передаем данные менеджера в ProjectsController
                ProjectsController projectsController = loader.getController();
                projectsController.setManager(loggedInManager);

                Stage stage = (Stage) emailField.getScene().getWindow();
                stage.setScene(new Scene(root));
            } catch (IOException e) {
                e.printStackTrace();
            }
        } else {
            Alert alert = new Alert(AlertType.ERROR);
            alert.setContentText("Invalid Credentials");
            alert.show();
        }
    }

    private Manager getLoggedInManager(String email, String password) {
        for (Manager manager : Manager.getInstances()) {
            if (manager.getEmail().equals(email) && manager.getPassword().equals(password)) {
                return manager;
            }
        }
        return null;
    }

    
    private boolean isValidLogin(String email, String password) {
        for (Manager manager : Manager.getInstances()) {
            if (manager.getEmail().equals(email) && manager.getPassword().equals(password)) {
                return true;
            }
        }
        return false;
    }
    
}
