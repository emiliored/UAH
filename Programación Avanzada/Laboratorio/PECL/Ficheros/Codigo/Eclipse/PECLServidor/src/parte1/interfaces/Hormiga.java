package parte1.interfaces;

import parte1.HormigaController;

public interface Hormiga {
	
	// Atributos comunes a todas las hormigas.
	public String getIdType();
	public int getIdHormiga();
	public HormigaController getControlador();
	public String getNombreHormiga();
}
