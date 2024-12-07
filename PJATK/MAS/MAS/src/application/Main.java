package application;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.stage.Stage;
import services.Serializator;
import javafx.scene.Parent;
import javafx.scene.Scene;

public class Main extends Application {
    private static final double WINDOW_WIDTH = 800;
    private static final double WINDOW_HEIGHT = 600;

    @Override
    public void start(Stage primaryStage) {
        try {
            Serializator.readData();

            Parent root = FXMLLoader.load(getClass().getResource("/fxml/Login.fxml"));
            Scene scene = new Scene(root, WINDOW_WIDTH, WINDOW_HEIGHT);
            scene.getStylesheets().add(getClass().getResource("/css/style.css").toExternalForm());

            primaryStage.setScene(scene);
            primaryStage.setResizable(false);
            primaryStage.show();

            primaryStage.sceneProperty().addListener((observable, oldScene, newScene) -> {
                if (newScene != null) {
                    primaryStage.setWidth(WINDOW_WIDTH);
                    primaryStage.setHeight(WINDOW_HEIGHT);
                    primaryStage.setResizable(false);
                }
            });

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        launch(args);
    }
}
