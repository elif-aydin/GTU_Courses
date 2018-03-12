import java.io.IOException;
import java.util.Arrays;
import java.util.Scanner;
import java.io.File;
import java.nio.file.Files;
import java.nio.file.Paths;

public class GeneralTestMain {

    public static void main(String[] args) {

        try {
            Files.createDirectories(Paths.get("TestResults"));
            testRandom("TestGraphs/randomTestGraph.txt");
            testBFS("TestGraphs/bfsTestGraph.txt");
            String [] testCCFiles = {"TestGraphs/ccTestGraph3.txt","TestGraphs/ccTestGraph2.txt",
                    "TestGraphs/ccTestGraph1.txt"};
            testCC(testCCFiles);
            String [] testBipartiteFiles = {"TestGraphs/bipartiteTestGraph1.txt","TestGraphs/bipartiteTestGraph2.txt",
                    "TestGraphs/bipartiteTestGraph3.txt","TestGraphs/bipartiteTestGraph4.txt",
                    "TestGraphs/bipartiteTestGraph5.txt", "TestGraphs/bipartiteTestGraph6.txt"};
            testBipartite(testBipartiteFiles);
        }catch(IOException e){
            System.out.println("File not found!" + e.getLocalizedMessage());
        }
    }

    private static void  testRandom(String filename) throws IOException{
        File graphData = new File(filename);
        Scanner scnr = new Scanner(graphData);
        ListGraph lgObj = (ListGraph) AbstractGraph.createGraph(scnr, true, "List");
        int edgesAdded = lgObj.addRandomEdgesToGraph(5);
        System.out.println("Random LG Directed: " + edgesAdded);
        lgObj.writeGraphToFile("TestResults/result11RandomLGDirected.txt");

        graphData = new File(filename);
        scnr = new Scanner(graphData);
        lgObj = (ListGraph) AbstractGraph.createGraph(scnr, false, "List");
        edgesAdded = lgObj.addRandomEdgesToGraph(5);
        System.out.println("Random LG Undirected: " + edgesAdded);
        lgObj.writeGraphToFile("TestResults/result12RandomLGUndirected.txt");

        graphData = new File(filename);
        scnr = new Scanner(graphData);
        MatrixGraph mgObj = (MatrixGraph) AbstractGraph.createGraph(scnr, true, "Matrix");
        edgesAdded = mgObj.addRandomEdgesToGraph(5);
        System.out.println("Random MG Directed: " + edgesAdded);
        mgObj.writeGraphToFile("TestResults/result13RandomMGDirected.txt");

        graphData = new File(filename);
        scnr = new Scanner(graphData);
        mgObj = (MatrixGraph) AbstractGraph.createGraph(scnr, false, "Matrix");
        edgesAdded = mgObj.addRandomEdgesToGraph(5);
        System.out.println("Random MG Undirected: " + edgesAdded);
        mgObj.writeGraphToFile("TestResults/result14RandomMGUndirected.txt");
    }

    private static void testBFS(String filename) throws IOException{
        File graphData = new File(filename);
        Scanner scnr = new Scanner(graphData);
        ListGraph lgObj = (ListGraph) AbstractGraph.createGraph(scnr, true, "List");
        int [] parentArray = lgObj.breadthFirstSearch(0);
        System.out.println("BFS LG Directed: " + Arrays.toString(parentArray));

        graphData = new File(filename);
        scnr = new Scanner(graphData);
        lgObj = (ListGraph) AbstractGraph.createGraph(scnr, false, "List");
        parentArray = lgObj.breadthFirstSearch(0);
        System.out.println("BFS LG Undirected: " + Arrays.toString(parentArray));

        graphData = new File(filename);
        scnr = new Scanner(graphData);
        MatrixGraph mgObj = (MatrixGraph) AbstractGraph.createGraph(scnr, true, "Matrix");
        parentArray = mgObj.breadthFirstSearch(0);
        System.out.println("BFS MG Directed: " + Arrays.toString(parentArray));

        graphData = new File(filename);
        scnr = new Scanner(graphData);
        mgObj = (MatrixGraph) AbstractGraph.createGraph(scnr, false, "Matrix");
        parentArray = mgObj.breadthFirstSearch(0);
        System.out.println("BFS MG Undirected: " + Arrays.toString(parentArray));
    }

    private static void testCC(String [] filenames) throws IOException{

        for(int j = 0 ; j < filenames.length ; ++j){
            File graphData = new File(filenames[j]);
            Scanner scnr = new Scanner(graphData);
            ListGraph lgObj = (ListGraph) AbstractGraph.createGraph(scnr, false, "List");
            Graph [] gArray = lgObj.getConnectedComponentUndirectedGraph();
            System.out.println("CC test " + (j+1) + " LG: " + gArray.length);
            for(int i=0; i < gArray.length ; ++i){
				if(gArray[i] != null){
					((AbstractGraphExtended)gArray[i]).writeGraphToFile("TestResults/result3" + (j+1) + i + "CCLG.txt");
				}
				else {
					System.out.println("CC element " + (j+1) + i + "is null");
				}
            }
        }
		
		System.out.println();

        for(int j = 0 ; j < filenames.length ; ++j){
            File graphData = new File(filenames[j]);
            Scanner scnr = new Scanner(graphData);
            MatrixGraph mgObj = (MatrixGraph) AbstractGraph.createGraph(scnr, false, "Matrix");
            Graph [] gArray = mgObj.getConnectedComponentUndirectedGraph();
            System.out.println("CC test " + (j+1) + " MG: " + gArray.length);
            for(int i=0; i < gArray.length ; ++i){
				if(gArray[i] != null){
					((AbstractGraphExtended)gArray[i]).writeGraphToFile("TestResults/result3" + (j+1) + i + "CCMG.txt");
				}
				else {
					System.out.println("CC element " + (j+1) + i + "is null");
				}
            }
        }

    }

    private static void testBipartite(String [] filenames) throws IOException{
        for(int j = 0 ; j < filenames.length ; ++j){
            File graphData = new File(filenames[j]);
            Scanner scnr = new Scanner(graphData);
            ListGraph lgObj = (ListGraph) AbstractGraph.createGraph(scnr, false, "List");
            boolean isBipartite = lgObj.isBipartiteUndirectedGraph();
            System.out.println("Bipartite test " + (j+1) + " LG: " + isBipartite);
        }
		
		System.out.println();

        for(int j = 0 ; j < filenames.length ; ++j){
            File graphData = new File(filenames[j]);
            Scanner scnr = new Scanner(graphData);
            MatrixGraph mgObj = (MatrixGraph) AbstractGraph.createGraph(scnr, false, "Matrix");
            boolean isBipartite = mgObj.isBipartiteUndirectedGraph();
            System.out.println("Bipartite test " + (j+1) + " MG: " + isBipartite);
        }
    }
}
