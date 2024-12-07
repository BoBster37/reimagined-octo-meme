package zad1;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GUI extends JFrame {
    private JTextField CountryField;
    private JButton CountryButton;
    private JTextField CityFIeld;
    private JTextField CurrencyField;
    private JLabel WeatherLabel;
    private JLabel RateLabel;
    private JLabel NBPLabel;
    private JButton InfoButton;
    private JPanel MyPanel;

    String country;

    public GUI(){

        this.setVisible(true);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.add(MyPanel);
        this.setSize(600,600);

        CountryButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                country = CountryField.getText();
            }
        });


        InfoButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Service s = new Service(country);
                WeatherLabel.setText(s.getWeather(CityFIeld.getText()));
                NBPLabel.setText((s.getNBPRate()).toString());
                RateLabel.setText((s.getRateFor(CurrencyField.getText())).toString());

            }
        });


    }
}
