/**
 *
 *  @author Haidukou Matsvei S26169
 *
 */
package zad1;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;
import javax.swing.plaf.synth.SynthOptionPaneUI;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLEncoder;
import java.util.Locale;
import java.util.stream.Collectors;

import java.io.IOException;

public class Service {

    String country;
    String currency_code;
    public Service(String string) {
        String urls = "https://api.opencagedata.com/geocode/v1/json?q="+string+"&key=2c3a7ce6759d4f258c58bc53db1288f3&countrycode=1";
        URL url;
        try {
            url = new URL(urls);

            InputStream inputStream = url.openConnection().getInputStream();
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream));
            String jsonString = bufferedReader.lines().collect(Collectors.joining());
            JSONParser parser = new JSONParser();
            JSONObject jsonObject = (JSONObject) parser.parse(jsonString);
            JSONArray results = (JSONArray) jsonObject.get("results");
            if (!results.isEmpty()) {
                JSONObject firstResult = (JSONObject) results.get(0);
                JSONObject components = (JSONObject) firstResult.get("components");
                JSONObject annotations = (JSONObject) firstResult.get("annotations");
                JSONObject currency = (JSONObject) annotations.get("currency");
                this.country = components.get("country_code").toString().toUpperCase(Locale.ENGLISH);
                this.currency_code = currency.get("iso_code").toString().toUpperCase(Locale.ENGLISH);
            }
        } catch (IOException | ParseException e) {
            throw new RuntimeException(e);
        }

    }

    public static void main(String[] args) throws MalformedURLException {

    }

    public String getWeather(String string) {


        String urlString = "http://api.openweathermap.org/geo/1.0/direct?q="+string+","+country + "&limit=1&appid=71170abf768266d0272d64a7cb0f7ba4";
        URL url;
        try {
            url = new URL(urlString);
            try{
                InputStream inputStream = url.openConnection().getInputStream();
                BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream));
                String jsonString = bufferedReader.lines().collect(Collectors.joining());
                JSONParser parser = new JSONParser();
                Object obj = parser.parse(jsonString);
                JSONArray jsonArray = (JSONArray)obj;
                JSONObject parse = (JSONObject)jsonArray.get(0);
                double lat = (double) parse.get("lat");
                double lon = (double)parse.get("lon");

                urlString = "https://api.openweathermap.org/data/2.5/weather?lat="+lat+"&lon="+lon+"&appid=71170abf768266d0272d64a7cb0f7ba4&units=metric";
                url = new URL(urlString);

                inputStream = url.openConnection().getInputStream();
                bufferedReader = new BufferedReader(new InputStreamReader(inputStream));
                jsonString = bufferedReader.lines().collect(Collectors.joining());
                inputStream.close();
                bufferedReader.close();
                return jsonString;


            } catch (MalformedURLException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
        catch (IOException e) {
            throw new RuntimeException(e);
        } catch (ParseException e) {
            throw new RuntimeException(e);
        }
        return null;
    }

    public Double getRateFor(String string) {
        String urlString = "https://api.exchangerate.host/latest?base="+currency_code+"&symbols="+string;
        URL url;
        try {

            url = new URL(urlString);
            InputStream inputStream = url.openConnection().getInputStream();
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream));
            String jsonString = bufferedReader.lines().collect(Collectors.joining());
            JSONParser parser = new JSONParser();
            JSONObject jsonObject = (JSONObject) parser.parse(jsonString);
            JSONObject rates = (JSONObject) jsonObject.get("rates");
            Double rate =Double.parseDouble(rates.get(string).toString().toUpperCase(Locale.ENGLISH)) ;
            bufferedReader.close();
            inputStream.close();
            return rate;
        } catch (MalformedURLException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (ParseException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return null;
    }

    public Double getNBPRate() {
        if(!country.equals("PL")) {
            String urls = "https://api.nbp.pl/api/exchangerates/rates/A/"+currency_code+"/last/1/?format=json";
            URL url;
            try {
                url = new URL(urls);
                InputStream inputStream = url.openConnection().getInputStream();
                BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream));
                String jsonString = bufferedReader.lines().collect(Collectors.joining());
                JSONParser parser = new JSONParser();
                JSONObject jsonObject = (JSONObject) parser.parse(jsonString);
                JSONArray rates = (JSONArray) jsonObject.get("rates");
                JSONObject rateFirst = (JSONObject) rates.get(0);
                double rate = (double) rateFirst.get("mid");
                inputStream.close();
                bufferedReader.close();
                return rate;
            } catch (MalformedURLException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            } catch (ParseException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }

            return null;
        }else{
            System.out.println("your currency is PLN");

        }
        return null;}
}


