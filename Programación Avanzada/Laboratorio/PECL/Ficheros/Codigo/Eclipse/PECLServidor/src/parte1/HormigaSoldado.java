package parte1;

import java.util.concurrent.atomic.AtomicInteger;

import parte1.Logging.LoggingException;
import parte1.interfaces.Hormiga;

public class HormigaSoldado extends Thread implements Hormiga{
	
	// Define sus propios valores de clase
	protected static String idType = "HS";
	protected static ThreadGroup grupoHilos = new ThreadGroup("HilosHS");
	protected static AtomicInteger contador = new AtomicInteger(0);
	
	static {
		HormigaController.setHormigasSoldado(grupoHilos);
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
	public HormigaSoldado(HormigaController hormigaController) throws LoggingException{
		super(grupoHilos, "");
		this.idHormiga = contador.getAndIncrement();
		this.controlador = hormigaController;
		super.setName(this.getNombreHormiga());
		try {
			this.controlador.addLog(this, ", creación de la hormiga soldado.");
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
		int i = 0;
		while(true) {
			if(this.controlador.getPararEjecucion().get()) { // Si está true, se suspende la hormiga.
				this.suspend();
			}
			/*
			 * Hace instrucción en la ZONA DE INSTRUCCIÓN, tardando un tiempo aleatorio de 
			 * entre 2 y 8 segundos en hacer esta operación. A continuación, descansa 2 
			 * segundos en la ZONA DE DESCANSO.
			 */
			this.controlador.entrarZonaInstruccion(this);
			this.controlador.entrarZonaDescanso(this, 2);
			i++;
			/*
			 * Todas las hormigas soldado, tras realizar 6 iteraciones completas de su acción principal, 
			 * pasan por la ZONA PARA COMER a reponer fuerzas y comer, consumiendo 1 unidad de 
			 * alimento. Esta operación tarda 3 segundos en realizarse.
			 */
			if(i == 6) {
				i = 0;
				this.controlador.entrarZonaComerConsumir(this);
			}
		}
	}
}
