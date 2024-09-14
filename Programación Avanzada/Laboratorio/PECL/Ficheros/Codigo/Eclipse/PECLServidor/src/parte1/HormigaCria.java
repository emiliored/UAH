package parte1;

import java.util.concurrent.atomic.AtomicInteger;

import parte1.Logging.LoggingException;
import parte1.interfaces.Hormiga;

public class HormigaCria extends Thread implements Hormiga{
	
	// Define sus propios valores de clase
	protected static String idType = "HC";
	protected static ThreadGroup grupoHilos = new ThreadGroup("HilosHC");
	protected static AtomicInteger contador = new AtomicInteger(0);
	
	static {
		HormigaController.setHormigasCria(grupoHilos);
	}
	
	// Atributos especificos de cada hormiga obrera
	private int idHormiga;
	private HormigaController controlador;
	
	// Métodos implementados en la interfaz
	@Override
	public String getIdType() {
		return idType;
	}
	@Override
	public int getIdHormiga() {
		return this.idHormiga;
	}
	
	@Override
	public HormigaController getControlador() {
		return this.controlador;
	}
	
	@Override
	public String getNombreHormiga() {
		return idType.concat(String.format("%04d", this.idHormiga));
	}
	
	// Métodos específicos para cada hormiga soldado
	public HormigaCria(HormigaController hormigaController) throws LoggingException{
		super(grupoHilos, "");
		this.idHormiga = contador.getAndIncrement();
		this.controlador = hormigaController;
		super.setName(this.getNombreHormiga());
		try {
			this.controlador.addLog(this, ", creación de la hormiga cria.");
		} catch (InterruptedException e) {
			throw new Logging.LoggingException(e.getMessage());
		}
	}

	// Override de los métodos de la clase Thread
	@Override
	public void run() {
		// Comportamiento que harán todas las hormigas al nacer.
		try {
			this.controlador.addLog(this, ", acaba de nacer...");
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		this.controlador.pasarTunelEntrada(this);
		
		/*
		 * Dado que las hormigas cría son muy débiles, en caso de que exista la 
		 * amenaza de un insecto invasor, todas ellas (tanto las creadas de forma 
		 *  previa a la amenaza como las generadas durante la amenaza) deben 
		 *  dejar lo que estén haciendo en ese momento y acudir rápidamente a la 
		 *  zona de REFUGIO, hasta que la amenaza haya desaparecido, volviendo 
		 *  entonces a su comportamiento habitual (iniciando su alimentación en la 
		 *  ZONA PARA COMER)
		 */
		if(HormigaController.getLuchandoInsectoInvasor().get()) {
			this.controlador.entrarZonaRefugio(this);
		}
		
		while(true) {
			if(this.controlador.getPararEjecucion().get()) { // Si está true, se suspende la hormiga.
				this.suspend();
			}
			/*
			 * Accede a la ZONA PARA COMER, tardando un tiempo aleatorio de entre 3 y 5 
			 *  segundos en alimentarse. A continuación, descansan 4 segundos en la 
			 *  ZONA DE DESCANSO
			 */
			this.controlador.entrarZonaComerConsumir(this, (int)((Math.random()*2) + 3));
			this.controlador.entrarZonaDescanso(this, 4);
		}
	}
}
