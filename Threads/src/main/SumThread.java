package main;

import java.util.concurrent.LinkedBlockingQueue;

public class SumThread implements Runnable {
    
	private LinkedBlockingQueue<String> dataQueue;
	private LinkedBlockingQueue<Float> sumQueue;
	
	private String data;
	private float sum;
	
    public SumThread(LinkedBlockingQueue<String> dataQueue, LinkedBlockingQueue<Float> sumQueue) {
    	
    	this.dataQueue = dataQueue;
    	this.sumQueue = sumQueue;
    	
    	this.data = "";
    	this.sum = 0;
    }

    @Override
    
    public void run() {
    	
        try {
        	
            while (true) {
            	
            	// Tomar y remover la cabeza de la fila de datos
            	
                data = dataQueue.take();
                
                try {
                	
                	// Transformar el dato recuperado en tipo flotante y realizar una suma acumulativa
                         
                    synchronized (this) {
                        sum += Float.parseFloat(data);
                    }
                    
                    // Añadir la suma a la fila de sumas para pasar datos al hilo de promedio
                    
                    sumQueue.add(sum);
                    
                    System.out.println("Sum: " + sum);
     
                } catch (NumberFormatException e) {
                    e.printStackTrace();
                }
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}