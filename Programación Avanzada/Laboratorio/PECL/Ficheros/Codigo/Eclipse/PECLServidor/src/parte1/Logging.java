package parte1;

import java.io.FileWriter;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.concurrent.BlockingQueue;

public class Logging implements Runnable{
	
	public static class LoggingException extends Exception{
		private static final long serialVersionUID = -3604260959065292002L;

		LoggingException(){
			super("No se ha configurado la cola del logging y es obligatoria para la ejecución de los hilos.");
		}
		
		LoggingException(String mensaje){
			super(mensaje);
		}
	}
	
	private BlockingQueue<String> listaLog;
	
	public BlockingQueue<String> getListaLog() {
		return listaLog;
	}
	
	public void setListaLog(BlockingQueue<String> listaLog) {
		this.listaLog = listaLog;
	}

	private String nombreFichero = "evolucionColonia.txt";

	public String getNombreFichero() {
		return nombreFichero;
	}

	public void setNombreFichero(String nombreFichero) {
		this.nombreFichero = nombreFichero;
	}
	
	public Logging(BlockingQueue<String> lista) {
		this.listaLog=lista;
	}
	
	public Logging(BlockingQueue<String> lista, String nombreFichero) {
		this.listaLog=lista;
		this.nombreFichero = nombreFichero;
	}

	@Override
	public void run() {
		try (FileWriter out = new FileWriter(nombreFichero)) {
			while(true) {
				out.write(listaLog.take()+"\n");
				out.flush();
			}
		} catch (InterruptedException | IOException e) {e.printStackTrace();} 
	}
	
	// Método de clase
	public static String getMensaje(String s) {
		s+="  ";
		Date fechaActual = new Date();
		String formato = "dd/MM/yyyy-HH:mm:ss:SSS";
		SimpleDateFormat sdf = new SimpleDateFormat(formato);
		return s.concat(sdf.format(fechaActual));
	}
}
