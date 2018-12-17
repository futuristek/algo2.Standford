#ifndef EDGE_HPP
#define EDGE_HPP
class Edge {
public:
    Edge() = default;

    Edge(int v, int w, double weight): v(v), w(w), weight(weight) { }
    
    double getWeight() const {
        return weight;
    }

    int either() const {
        return v;
    }

    int other(int vertex) const {
        if (vertex == v)
            return w;
        else
            return v;
    }

    bool operator==(const Edge e) const {
        return e.weight == weight;
    }

    bool operator>(const Edge e) const {
        return e.weight > weight;
    }

    bool operator<(const Edge e) const {
        return e.weight < weight;
    }

private:
    int w;
    int v;
    double weight;
};
#endif