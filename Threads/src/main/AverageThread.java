package main;

import java.util.concurrent.LinkedBlockingQueue;

public class AverageThread implements Runnable {
    
	private LinkedBlockingQueue<Float> sumQueue;
	
	private float currentSum;
	private float average;

    public AverageThread(LinkedBlockingQueue<Float> sumQueue) {
    	
    	this.sumQueue = sumQueue;
    	
    	this.currentSum = 0;
    	this.average = 0;
    }

    @Override
    
    public void run() {
    	
        try {
        	
            while (true) {
            	
            	// Tomar y remover la cabeza de la fila de datos
            	
            	currentSum = sumQueue.take();
                
                try {
                	
                	// Transformar el dato recuperado en tipo flotante y realizar una suma acumulativa
                         
                    synchronized (this) {
                    	
                    	// Calcula el promedio ponderado
                    	
                        average = (average * 0.9f) + (currentSum * 0.1f);
                    	
                    	// System.out.println("a");
                    }
                    
                    System.out.println("Weighted average: " + average);
     
                } catch (NumberFormatException e) {
                    e.printStackTrace();
                }
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}