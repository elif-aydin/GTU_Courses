import bulut.BulutServer;

import javax.swing.*;
import java.rmi.AlreadyBoundException;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.util.Random;

public class Main {


    public static void main(String[] args) throws ClassNotFoundException, UnsupportedLookAndFeelException, InstantiationException, IllegalAccessException, RemoteException, AlreadyBoundException {

        // generate an apikey for this client.
        Random rnd = new Random();
        String uniqueApiKey = "BLT_" + (rnd.nextInt(1000) + 1) * (rnd.nextInt(1000) + 1);

        // create a registry on port 1888.
        LocateRegistry.createRegistry(1888);

        // create the server and bind it.
        BulutServer server = new BulutServer(uniqueApiKey, 0);

        // create client and run it in its own thread.
        UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        SwingUtilities.invokeLater(() -> {
            MainGui mainGui = null;
            try {
                mainGui = new MainGui(uniqueApiKey, 0);
            } catch (RemoteException e) {
                e.printStackTrace();
            } catch (NotBoundException e) {
                e.printStackTrace();
            }
            mainGui.setVisible(true);
        });
    }
}
