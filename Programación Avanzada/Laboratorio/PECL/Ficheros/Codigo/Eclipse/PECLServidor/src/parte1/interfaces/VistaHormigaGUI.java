package parte1.interfaces;

import java.util.Set;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * @author Emilio Macías Do Santos
 *
 *	Esta interfaz sirve para que la vista GUI.java pueda saber qué métodos llamar al controlador,
 *	de esta forma se implementa el MVC.
 *
 *	La vista no verá nada más que los métodos que deba saber.
 */
public interface VistaHormigaGUI{
	// Getter y Setters públicos
	public Set<String> gethDentroColonia();

	public Set<String> gethFueraColonia();

	public Set<String> gethBuscandoComida();

	public Set<String> gethRepeliendoInsecto();

	public Set<String> gethAlmacenComida();

	public Set<String> gethLlevandoZonaComer();

	public Set<String> gethZonaInstruccion();

	public Set<String> gethZonaDescanso();

	public Set<String> gethZonaComer();

	public Set<String> gethRefugio();
	
	public int getUnidadesComidaAlmacen();

	public AtomicInteger getUnidadesComidaZonaComer();
	
	public AtomicBoolean getPararEjecucion();
	
	// Métodos para parar la ejecucion de las hormigas dando al botón Parar
	public void pararEjecucion();
	public void continuarEjecucion();
	// Método para generar un insecto invasor
	public void generarInsectoInvasor();
	
	// Métodos que utilizan un semáforo para controlar los eventos.
	public void cambioAdquire() throws InterruptedException;
	
	public void cambioRelease();
	
}
