import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Arrays;
import java.util.Scanner;

public class Main
{
    public static void main(String[] args)
    {
        testFirst();
        testSecond();
        testThird();
        testFourth();
    }

    public static void testFirst()
    {
        Scanner scan = null;
        ListGraph listGraph = null;
        MatrixGraph matrixGraph = null;
        try
        {
            // list
            scan = new Scanner(new File("test.txt"));
            System.out.println("Testing addRandomEdgesToGraph() with 6 for List Graph from test.txt (for directed graph)");
            listGraph = (ListGraph) AbstractGraph.createGraph(scan, true, "List");
            listGraph.addRandomEdgesToGraph(6);
            System.out.println("Result is saved in resultListForAdd.txt");
            listGraph.writeGraphToFile("resultListForAdd.txt");
            scan.close();

            scan = new Scanner(new File("test2.txt"));
            System.out.println("Testing addRandomEdgesToGraph() with 6 for List Graph from test2.txt(for undirected graph)");
            listGraph = (ListGraph) AbstractGraph.createGraph(scan, false, "List");
            listGraph.addRandomEdgesToGraph(6);
            System.out.println("Result is saved in resultListForAdd2.txt");
            listGraph.writeGraphToFile("resultListForAdd2.txt");
            scan.close();

            // matrix
            scan = new Scanner(new File("test.txt"));
            System.out.println("\nTesting addRandomEdgesToGraph() with 5 for Matrix Graph from test.txt (for directed graph)");
            matrixGraph = (MatrixGraph) AbstractGraph.createGraph(scan, true, "Matrix");
            matrixGraph.addRandomEdgesToGraph(5);
            System.out.println("Result is saved in resultMatrixForAdd.txt");
            matrixGraph.writeGraphToFile("resultMatrixForAdd.txt");
            scan.close();

            scan = new Scanner(new File("test2.txt"));
            System.out.println("Testing addRandomEdgesToGraph() with 5 for Matrix Graph from test2.txt (for undirected graph)");
            matrixGraph = (MatrixGraph) AbstractGraph.createGraph(scan, false, "Matrix");
            matrixGraph.addRandomEdgesToGraph(5);
            System.out.println("Result is saved in resultMatrixForAdd2.txt");
            matrixGraph.writeGraphToFile("resultMatrixForAdd2.txt");
            scan.close();
            System.out.println("\n");
        }
        catch (FileNotFoundException e)
        {
            e.printStackTrace();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
    }

    public static void testSecond()
    {
        Scanner scan = null;
        ListGraph listGraph = null;
        MatrixGraph matrixGraph = null;
        try
        {
            // list
            scan = new Scanner(new File("test.txt"));
            System.out.println("Testing breadthFirstSearch() with 0 for List Graph from test.txt (for directed graph)");
            listGraph = (ListGraph) AbstractGraph.createGraph(scan, true, "List");
            int[] res = listGraph.breadthFirstSearch(0);
            System.out.println("Result: " + Arrays.toString(res));
            scan.close();

            scan = new Scanner(new File("test2.txt"));
            System.out.println("Testing breadthFirstSearch() with 0 for List Graph from test2.txt(for undirected graph)");
            listGraph = (ListGraph) AbstractGraph.createGraph(scan, false, "List");
            res = listGraph.breadthFirstSearch(0);
            System.out.println("Result: " + Arrays.toString(res));
            scan.close();

            // matrix
            scan = new Scanner(new File("test.txt"));
            System.out.println("\nTesting breadthFirstSearch() with 0 for Matrix Graph from test.txt (for directed graph)");
            matrixGraph = (MatrixGraph) AbstractGraph.createGraph(scan, true, "Matrix");
            res = matrixGraph.breadthFirstSearch(0);
            System.out.println("Result: " + Arrays.toString(res));
            scan.close();

            scan = new Scanner(new File("test2.txt"));
            System.out.println("Testing breadthFirstSearch() with 0 for Matrix Graph from test2.txt (for undirected graph)");
            matrixGraph = (MatrixGraph) AbstractGraph.createGraph(scan, false, "Matrix");
            res = matrixGraph.breadthFirstSearch(0);
            System.out.println("Result: " + Arrays.toString(res));
            scan.close();

            System.out.println("\n");
        }
        catch (FileNotFoundException e)
        {
            e.printStackTrace();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
    }

    public static void testThird()
    {
        Scanner scan = null;
        ListGraph listGraph = null;
        MatrixGraph matrixGraph = null;
        try
        {
            // list
            scan = new Scanner(new File("testConnected.txt"));
            System.out.println("Testing getConnectedComponentUndirectedGraph() for List Graph from testConnected.txt(for undirected graph)");
            listGraph = (ListGraph) AbstractGraph.createGraph(scan, false, "List");
            Graph[] res = listGraph.getConnectedComponentUndirectedGraph();
            int counter = 1;
            for (Graph graph : res)
            {
                ((AbstractGraphExtended) graph).writeGraphToFile("connectedResListUndirected" + (counter++) + ".txt");
            }
            System.out.println("Results are saved to connectedResListUndirected[num] files.");
            scan.close();

            // matrix
            scan = new Scanner(new File("testConnected.txt"));
            System.out.println("Testing getConnectedComponentUndirectedGraph() for Matrix Graph from testConnected.txt (for undirected graph)");
            matrixGraph = (MatrixGraph) AbstractGraph.createGraph(scan, false, "Matrix");
            res = matrixGraph.getConnectedComponentUndirectedGraph();
            counter = 1;
            for (Graph graph : res)
            {
                ((AbstractGraphExtended) graph).writeGraphToFile("connectedResMatrixUndirected" + (counter++) + ".txt");
            }
            System.out.println("Results are saved to connectedResMatrixUndirected[num] files.");
            scan.close();

            System.out.println("\n");
        }
        catch (FileNotFoundException e)
        {
            e.printStackTrace();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }

    }

    public static void testFourth()
    {
        Scanner scan = null;
        ListGraph listGraph = null;
        MatrixGraph matrixGraph = null;
        try
        {
            // list
            scan = new Scanner(new File("bipartiteTest.txt"));
            System.out.println("Testing isBipartiteUndirectedGraph() for List Graph from bipartiteTest.txt");
            listGraph = (ListGraph) AbstractGraph.createGraph(scan, false, "List");
            boolean res = listGraph.isBipartiteUndirectedGraph();
            System.out.println("Result: " + res);
            scan.close();

            scan = new Scanner(new File("test2.txt"));
            System.out.println("Testing isBipartiteUndirectedGraph() for List Graph from test2.txt");
            listGraph = (ListGraph) AbstractGraph.createGraph(scan, false, "List");
            res = listGraph.isBipartiteUndirectedGraph();
            System.out.println("Result: " + res);
            scan.close();

            // matrix
            scan = new Scanner(new File("bipartiteTest.txt"));
            System.out.println("\nTesting isBipartiteUndirectedGraph() for Matrix Graph from bipartiteTest.txt");
            matrixGraph = (MatrixGraph) AbstractGraph.createGraph(scan, false, "Matrix");
            res = matrixGraph.isBipartiteUndirectedGraph();
            System.out.println("Result: " + res);
            scan.close();

            scan = new Scanner(new File("test2.txt"));
            System.out.println("Testing isBipartiteUndirectedGraph() for Matrix Graph from test2.txt");
            matrixGraph = (MatrixGraph) AbstractGraph.createGraph(scan, false, "Matrix");
            res = matrixGraph.isBipartiteUndirectedGraph();
            System.out.println("Result: " + res);
            scan.close();

            System.out.println("\n");
        }
        catch (FileNotFoundException e)
        {
            e.printStackTrace();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
    }
}
