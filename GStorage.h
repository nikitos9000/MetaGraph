#ifndef GSTORAGE_H
#define GSTORAGE_H

#include <map>
#include <stdexcept>
#include <string>

#include "DiGraph.h"

#include "VertexSet.h"
#include "ArcSet.h"
#include "Path.h"

using namespace std;

class GStorageVertexSet
{
    protected:
        string _name;
        VertexSet _vertex_set;

    public:
        typedef VertexSet::VertexIterator VertexIterator;

        GStorageVertexSet(const VertexSet& vertex_set, const string& name);
        GStorageVertexSet(const GStorageVertexSet& other);

        VertexSet& getVertexSet();
        const VertexSet& getVertexSet() const;

        void setName(const string& name);
        const string& getName() const;
};

class GStorageArcSet
{
    protected:
        string _name;
        ArcSet _arc_set;

    public:
        typedef ArcSet::ArcIterator ArcIterator;

        GStorageArcSet(const ArcSet& arc_set, const string& name);
        GStorageArcSet(const GStorageArcSet& other);

        ArcSet& getArcSet();
        const ArcSet& getArcSet() const;

        void setName(const string& name);
        const string& getName() const;
};

class GStoragePath
{
    protected:
        string _name;
        Path _path;

    public:
        typedef Path::VertexIterator VertexIterator;
        typedef Path::ArcIterator ArcIterator;

        GStoragePath(const Path& path, const string& name);
        GStoragePath(const GStoragePath& other);

        Path& getPath();
        const Path& getPath() const;

        void setName(const string& name);
        const string& getName() const;
};

class GStorageDiGraph
{
    protected:
        string _name;
        DiGraph _digraph;
        map<size_t, GStorageVertexSet> _vertex_set_list;
        map<size_t, GStorageArcSet> _arc_set_list;
        map<size_t, GStoragePath> _path_list;

        size_t _newVertexSetId() const;
        size_t _newArcSetId() const;
        size_t _newPathId() const;

    public:
        typedef map<size_t, GStorageVertexSet>::const_iterator VertexSetIterator;
        typedef map<size_t, GStorageArcSet>::const_iterator ArcSetIterator;
        typedef map<size_t, GStoragePath>::const_iterator PathIterator;
        typedef DiGraph::Properties Properties;

        GStorageDiGraph(const DiGraph& digraph, const string& name);
        GStorageDiGraph(const GStorageDiGraph& gstorage_digraph);

        DiGraph& getDiGraph();
        const DiGraph& getDiGraph() const;

        void setName(const string& name);
        const string& getName() const;

        size_t addVertexSet(const GStorageVertexSet& vertex_set);
        size_t addArcSet(const GStorageArcSet& arc_set);
        size_t addPath(const GStoragePath& path);

        bool hasVertexSet(size_t id) const;
        bool hasArcSet(size_t id) const;
        bool hasPath(size_t id) const;

        GStorageVertexSet& getVertexSet(size_t id);
        const GStorageVertexSet& getVertexSet(size_t id) const;

        GStorageArcSet& getArcSet(size_t id);
        const GStorageArcSet& getArcSet(size_t id) const;

        GStoragePath& getPath(size_t id);
        const GStoragePath& getPath(size_t id) const;

        void removeVertexSet(size_t id);
        void removeArcSet(size_t id);
        void removePath(size_t id);

        VertexSetIterator beginVertexSetIterator() const;
        VertexSetIterator endVertexSetIterator() const;

        ArcSetIterator beginArcSetIterator() const;
        ArcSetIterator endArcSetIterator() const;

        PathIterator beginPathIterator() const;
        PathIterator endPathIterator() const;
};

class GStorage
{
    protected:
        map<size_t, GStorageDiGraph> _gstorage_digraph_list;

        size_t _newDiGraphId() const;

    public:
        typedef map<size_t, GStorageDiGraph>::const_iterator DiGraphIterator;

        GStorage();
        GStorage(const GStorage& GStorage);
        ~GStorage();

        size_t addDiGraph(const GStorageDiGraph& digraph);

        bool hasDiGraph(size_t id) const;

        GStorageDiGraph& getDiGraph(size_t id);
        const GStorageDiGraph& getDiGraph(size_t id) const;

        void removeDiGraph(size_t id);

        DiGraphIterator beginDiGraphIterator() const;
        DiGraphIterator endDiGraphIterator() const;
};

#endif // GSTORAGE_H
