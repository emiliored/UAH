package parte2.interfaces;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.Set;

/**
 * @author Emilio Macías Do Santos
 *
 *	Esta interfaz sirve para que la vista GUI.java pueda saber qué métodos llamar al controlador,
 *	de esta forma se implementa el MVC.
 *
 *	La vista no verá nada más que los métodos que deba saber.
 */
public interface VistaClienteRMI extends Remote{
	// Getter y Setters públicos
	public Set<String> gethDentroColoniaRMI() throws RemoteException;

	public Set<String> gethFueraColoniaRMI() throws RemoteException;

	public Set<String> gethZonaInstruccionRMI() throws RemoteException;
	
	public Set<String> gethRepeliendoInsectoRMI() throws RemoteException;

	public Set<String> gethZonaComerRMI() throws RemoteException;

	public Set<String> gethRefugioRMI() throws RemoteException;
	
	// Método para generar un insecto invasor
	public void generarInsectoInvasorRMI() throws RemoteException;
	
	// Métodos que utilizan un semáforo para controlar los eventos.
	public void cambioAdquireRMI() throws InterruptedException, RemoteException;
	
	public void cambioReleaseRMI() throws RemoteException;
	
}
