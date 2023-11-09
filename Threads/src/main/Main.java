package main;

import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;

import java.io.IOException;
import java.net.InetSocketAddress;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;

import java.util.concurrent.LinkedBlockingQueue;

public class Main {

	// Crear filas compartidas para pasar datos entre hilos
	
	private static LinkedBlockingQueue<String> dataQueue = new LinkedBlockingQueue<>();
	private static LinkedBlockingQueue<Float> sumQueue = new LinkedBlockingQueue<>();
	
    public static void main(String[] args) {
    	
        try {
        	// Crear un servidor HTTP en el puerto 8080
        	
            int port = 8080;
            HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);

            // Crear un contexto para el punto final
            
            server.createContext("/distanceTopic", new Handler());
            
            // Comenzar servidor 
            
            server.start();
            System.out.println("Server is running on port " + port);
    		
    		// Crear y comenzar hilos para sumar datos y realizar promedio

    		Thread sumThread = new Thread(new SumThread(dataQueue, sumQueue));
    		sumThread.start(); 
    		
    		Thread averageThread = new Thread(new AverageThread(sumQueue));
    		averageThread.start();
    		
        } catch (IOException e) {
            e.printStackTrace();
        }   
    }

    static class Handler implements HttpHandler {
        
    	@Override
    	
    	public void handle(HttpExchange exchange) throws IOException {
    		
            // Checar el método de la petición (POST)
    		
            if ("POST".equals(exchange.getRequestMethod())) {
            	
                // Acceder al flujo de entrada para leer el cuerpo de la petición
            	
                InputStream requestBody = exchange.getRequestBody();
                InputStreamReader isr = new InputStreamReader(requestBody);
                BufferedReader br = new BufferedReader(isr);

                StringBuilder requestData = new StringBuilder();
                String line;
                
                while ((line = br.readLine()) != null) {
                    requestData.append(line);
                }

                // Procesar los datos del cuerpo de la petición
                
                String postData = requestData.toString();

                // Cerrar los flujos
                
                br.close();
                isr.close();
                requestBody.close();

                // Añadir los datos de la petición POST a la fila de datos
                
                dataQueue.add(postData);

                // Enviar una respuesta
                
                String response = "Data received successfully";
                exchange.sendResponseHeaders(200, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } 
            else {
            	
            	// Proporcionar un mensaje de error en caso de manejar otros métodos HTTP
            	
                String response = "Unsupported method: " + exchange.getRequestMethod();
                exchange.sendResponseHeaders(405, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }
    }   
}
