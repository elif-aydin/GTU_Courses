import java.io.BufferedWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Map;
import java.util.List;
import java.util.Queue;
import java.util.LinkedList;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Random;
import java.util.HashSet;
import java.util.Set;
import java.util.Iterator;
import java.util.HashMap;
import java.util.Collections;


public abstract class AbstractGraphExtended extends AbstractGraph
{
    /**
     * Construct a graph with the specified number of vertices
     * and the directed flag. If the directed flag is true,
     * this is a directed graph.
     *
     * @param numV     The number of vertices
     * @param directed The directed flag
     */
    public AbstractGraphExtended(int numV, boolean directed)
    {
        super(numV, directed);
    }

    /**
     * Adds different random edges to the graph.
     * @param edgeLimit
     * @return number of inserted edges
     */
    public int addRandomEdgesToGraph(int edgeLimit)
    {
        Random random = new Random();
        int counter = 0;
        int numEdges = random.nextInt(edgeLimit);

        for (int i = 0; i < numEdges; i++)
        {
            int source = 0, destination = 0;
            // try to get different values for source and target
            while (source == destination)
            {
                source = random.nextInt(this.getNumV());
                destination = random.nextInt(this.getNumV());
            }

            Edge edge = new Edge(source, destination, 1);
            if (!isEdge(source, destination))
            {
                this.insert(edge);
                ++counter;
            }
        }
        return counter;
    }

    /**
     * Breadth-first search wrapper. Calls actual breadth-search method and then
     * converts the parent list to array to return.
     * @param start from vertex start
     * @return an array which contains the predecessor of each vertex in the breadth-first search tree
     */
    public int[] breadthFirstSearch(int start)
    {
        List<Integer> result = new ArrayList<>();
        breadthFirstSearch(start, result);
        int[] parentArr = new int[result.size()];
        int i = 0;
        for (int integer : result)
            parentArr[i++] = integer;

        return parentArr;
    }

    /**
     * Performs breadth-first search from given starting vertex and puts
     * predecessors to the result list.
     * Additionally, it looks if there is any cycle in the graph. If there is,
     * then this is not a bipartite graph. If not, it is bipartite.
     * @param start
     * @param result
     * @return true if bipartite, false otherwise.
     */
    private boolean breadthFirstSearch(int start, List<Integer> result)
    {
        Queue <Integer> queue = new LinkedList<>();
        int[] level = new int[this.getNumV()];
        int[] parent = new int[this.getNumV()];
        for (int i = 0; i < this.getNumV(); i++)
        {
            parent[i] = -1;
            level[i] = 0;
        }

        boolean[] identified = new boolean[this.getNumV()];
        boolean returnVal = true;

        identified[start] = true;
        queue.offer(start);
        while (!queue.isEmpty())
        {
            int current = queue.remove();
            Iterator <Edge> itr = this.edgeIterator(current);
            while (itr.hasNext())
            {
                Edge edge = itr.next();
                int neighbor = edge.getDest();
                if (!identified[neighbor])
                {
                    identified[neighbor] = true;
                    level[current] = level[neighbor] + 1;
                    queue.offer(neighbor);
                    parent[neighbor] = current;
                }
                else if (level[current] == level[neighbor])
                {
                    returnVal = false;
                }
            }
        }

        for (int integer : parent)
            result.add(integer);

        return returnVal;
    }

    /**
     * Gets different connected vertices. Uses depth-first search.
     * @return each connected component
     */
    public Graph[] getConnectedComponentUndirectedGraph()
    {
        if(this.isDirected())
            return null;

        List<Graph> resultGraphs = new ArrayList<>();
        boolean[] visited = new boolean[this.getNumV()];

        for (int i = 0; i < this.getNumV(); i++)
        {
            if (!visited[i])
            {
                List<Edge> result = new ArrayList<>();
                dfsRec(i, visited, result);
                Map<Integer, Integer> reducingMap = getReducingMap(result);

                if (!result.isEmpty())
                {
                    AbstractGraph graph = null;
                    if (this instanceof ListGraph)
                        graph = new ListGraph(reducingMap.size(), false);
                    else if (this instanceof MatrixGraph)
                        graph = new MatrixGraph(reducingMap.size(), false);
                    else
                        return null;

                    for (Edge edge : result)
                        graph.insert(new Edge(reducingMap.get(edge.getSource()), reducingMap.get(edge.getDest())));

                    resultGraphs.add(graph);
                }
            }
        }
        Graph[] arr = new Graph[resultGraphs.size()];
        for (int i = 0; i < arr.length; i++)
        {
            arr[i] = resultGraphs.get(i);
        }
        return arr;
    }

    /**
     * Checks if there is any cycle in the graph. If there is,
     * then this is not a bipartite graph. If not, it is bipartite.
     *
     * Calls breadth-first search.
     * @return true or false according to bipartism
     */
    public boolean isBipartiteUndirectedGraph()
    {
        if(this.isDirected())
            return false;

        return breadthFirstSearch(0, new ArrayList<>());
    }


    /**
     * Writes this graph to the file.
     * @param fileName
     */
    public void writeGraphToFile(String fileName)
    {
        String s = this.toString();
        // automatically release/close the buffer with this try block
        try (BufferedWriter writer = Files.newBufferedWriter(Paths.get(fileName)))
        {
            writer.write(s);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Maps the vertices in the given edges to the integers starting from 0.
     * First, sorts the vertices and then maps starting from 0.
     * @param edges
     * @return
     */
    private Map<Integer, Integer> getReducingMap(List<Edge> edges)
    {
        Set<Integer> temp = new HashSet<>();
        for (Edge edge : edges)
        {
            temp.add(edge.getSource());
            temp.add(edge.getDest());
        }

        List<Integer> differentVertices = new ArrayList<>(temp);
        Collections.sort(differentVertices);

        Map<Integer, Integer> reducingMap = new HashMap<>();
        int reduced = 0;
        for (Integer old : differentVertices)
            reducingMap.put(old, reduced++);

        return reducingMap;
    }

    /**
     * Performs depth-first search on the graph. Puts visited edges to the
     * result list.
     * @param v
     * @param visited
     * @param result
     */
    private void dfsRec(int v, boolean[] visited, List<Edge> result)
    {
        visited[v] = true;
        Iterator <Edge> itr = this.edgeIterator(v);
        while (itr.hasNext())
        {
            Edge edge = itr.next();
            int neighbor = edge.getDest();
            if (!visited[neighbor])
            {
                result.add(edge);
                dfsRec(neighbor, visited, result);
            }
        }
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(this.getNumV()).append("\n");
        for (int i = 0; i < this.getNumV(); i++)
        {
            Iterator<Edge> it = this.edgeIterator(i);
            while (it.hasNext())
            {
                Edge e = it.next();
                sb.append(e.getSource()).append(" ").append(e.getDest()).append("\n");
            }
        }

        return sb.toString();
    }
}
