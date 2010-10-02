#ifndef GMODEL_H
#define GMODEL_H

#include <list>
#include <memory>

#include "GStorage.h"
#include "GView.h"

using namespace std;

class GStorage;
class GView;

class GModelDiGraphIterator;
class GModelDiGraph;
class GModelDiGraphProperties;
class GModelVertexSetIterator;
class GModelVertexSet;
class GModelArcSetIterator;
class GModelArcSet;
class GModelPathIterator;
class GModelPath;

#include <list>

struct GModelStateSelected
{
    private:
        unsigned int _value;

    public:
        const static int None = 0;
        const static int DiGraph = 1;

        GModelStateSelected() : _value(None) { }
        GModelStateSelected(unsigned int value) : _value(value) { }

        bool operator==(const unsigned int& value) { return value == _value; }
        bool operator!=(const unsigned int& value) { return value != _value; }
        bool operator==(const GModelStateSelected& other) { return other._value == _value; }
        bool operator!=(const GModelStateSelected& other) { return other._value != _value; }
        GModelStateSelected& operator=(const unsigned int& value) { _value = value; return *this; }
};

struct GModelStateDiGraphSelected
{
    private:
        unsigned int _value;

    public:
        const static unsigned int None = 0;
        const static unsigned int Vertex = 1;
        const static unsigned int VertexMulti = 2;
        const static unsigned int Arc = 4;
        const static unsigned int ArcMulti = 8;
        const static unsigned int VertexSet = 16;
        const static unsigned int VertexSetMulti = 32;
        const static unsigned int ArcSet = 64;
        const static unsigned int ArcSetMulti = 128;
        const static unsigned int Path = 256;
        const static unsigned int PathMulti = 512;

        GModelStateDiGraphSelected() : _value(None) { }
        GModelStateDiGraphSelected(unsigned int value) : _value(value) { }

        unsigned int value() const { return _value; }

//        bool operator==(const unsigned int& value) { return value == _value; }
//        bool operator!=(const unsigned int& value) { return value != _value; }
        bool operator==(const GModelStateDiGraphSelected& other) { return other._value == _value; }
        bool operator!=(const GModelStateDiGraphSelected& other) { return other._value != _value; }
        GModelStateDiGraphSelected& operator=(const unsigned int& value) { _value = value; return *this; }
};

class GModelState
{
    protected:
        enum AppendMode { AppendModeUnion, AppendModeSubtraction };

        GStorage& _gstorage;

        GModelStateSelected _selected;
        size_t _id;

        GModelStateDiGraphSelected _selected_digraph;
        unordered_map< vertex_t, size_t, vertex_hash > _vertex_view;
        unordered_map< arc_t, size_t, arc_hash > _arc_view;

        list< pair< vertex_t, AppendMode > > _vertex_list;
        list< pair< arc_t, AppendMode > > _arc_list;
        list< size_t > _vertex_set_list;
        list< size_t > _arc_set_list;
        list< size_t > _path_list;

        void _checkDiGraphVertex(size_t id);
        void _checkDiGraphArc(size_t start_id, size_t end_id);
        void _checkDiGraphVertexSet(size_t id);
        void _checkDiGraphArcSet(size_t id);
        void _checkDiGraphPath(size_t id);

/*        void _appendDiGraphVertex(size_t id, AppendMode append_mode);
        void _appendDiGraphArc(size_t start_id, size_t end_id, AppendMode append_mode);
        void _appendDiGraphVertexSet(size_t id);
        void _appendDiGraphArcSet(size_t id);
        void _appendDiGraphPath(size_t id); */

    public:
        GModelState(GStorage& gstorage);

        void selectDiGraph(size_t id);
        void selectDiGraphVertex(size_t id);
        void selectDiGraphArc(size_t start_id, size_t end_id);
        void selectDiGraphVertexSet(size_t id);
        void selectDiGraphArcSet(size_t id);
        void selectDiGraphPath(size_t id);

        void selectAddDiGraphVertex(size_t id);
        void selectAddDiGraphArc(size_t start_id, size_t end_id);
        void selectAddDiGraphVertexSet(size_t id);
        void selectAddDiGraphArcSet(size_t id);
        void selectAddDiGraphPath(size_t id);

        void selectRemoveDiGraphVertex(size_t id);
        void selectRemoveDiGraphArc(size_t start_id, size_t end_id);
        void selectRemoveDiGraphVertexSet(size_t id);
        void selectRemoveDiGraphArcSet(size_t id);
        void selectRemoveDiGraphPath(size_t id);

        void save();

        void clear();
        void clearDiGraph();

        void createNewDiGraph(const string& name);
        void createNewDiGraphVertexSet(const string& name);
        void createNewDiGraphArcSet(const string& name);
        void createNewDiGraphPath(const string& name);

        GModelStateSelected typeSelected() const;
        GModelStateDiGraphSelected typeDiGraphSelected() const;

        size_t countDiGraphVertexSelected(size_t id) const;
        size_t countDiGraphArcSelected(size_t start_id, size_t end_id) const;

        bool isDiGraphVertexSetSelected(size_t id) const;
        bool isDiGraphArcSetSelected(size_t id) const;
        bool isDiGraphPathSelected(size_t id) const;

        bool canSave() const;
};

class GModelDiGraphIterator
{
    protected:
        map<size_t, GStorageDiGraph>::const_iterator _iterator;

    public:
        GModelDiGraphIterator(const GStorage::DiGraphIterator& iterator);
        GModelDiGraphIterator(const GModelDiGraphIterator& other);

        pair< size_t, GModelDiGraph > operator*() const;
        GModelDiGraphIterator& operator++();
        GModelDiGraphIterator operator++(int);
        bool operator==(const GModelDiGraphIterator& other) const;
        bool operator!=(const GModelDiGraphIterator& other) const;
};

class GModelDiGraph
{
    protected:
        const GStorageDiGraph& _gstorage_digraph;

    public:
//        typedef * VertexIterator;
//        typedef * ArcIterator;
//        typedef * VertexOutIterator;
//        typedef * VertexInIterator;
//        typedef * ArcOutIterator;
//        typedef * ArcInIterator;

        typedef GModelVertexSetIterator VertexSetIterator;
        typedef GModelArcSetIterator ArcSetIterator;
        typedef GModelPathIterator PathIterator;

        GModelDiGraph(const GStorageDiGraph& gstorage_digraph);
        GModelDiGraph(const GModelDiGraph& gmodel_digraph);

        const string& name() const;

        size_t vertexCount() const;
        size_t arcCount() const;

        GModelDiGraphProperties getProperties() const;

        GModelPath getPath(size_t id) const;
        GModelVertexSet getVertexSet(size_t id) const;
        GModelArcSet getArcSet(size_t id) const;

        VertexSetIterator beginVertexSetIterator() const;
        VertexSetIterator endVertexSetIterator() const;

        ArcSetIterator beginArcSetIterator() const;
        ArcSetIterator endArcSetIterator() const;

        PathIterator beginPathIterator() const;
        PathIterator endPathIterator() const;
};

class GModelDiGraphProperties
{
    protected:
        const GStorageDiGraph::Properties& _properties;

    public:
        GModelDiGraphProperties(const GStorageDiGraph::Properties& digraph_properties);
        GModelDiGraphProperties(const GModelDiGraphProperties& gmodel_digraph_properties);

        bool isWeaklyConnectedDefined() const;
        bool isStronglyConnectedDefined() const;
        bool isAcyclicDefined() const;
        bool isCompleteDefined() const;
        bool isSimpleDefined() const;
        bool isTreeDefined() const;

        bool isWeaklyConnected() const;
        bool isStronglyConnected() const;
        bool isAcyclic() const;
        bool isComplete() const;
        bool isSimple() const;
        bool isTree() const;
};

class GModelVertexSetIterator
{
    protected:
        map<size_t, GStorageVertexSet>::const_iterator _iterator;

    public:
        GModelVertexSetIterator(const GStorageDiGraph::VertexSetIterator& iterator);
        GModelVertexSetIterator(const GModelVertexSetIterator& other);

        pair< size_t, GModelVertexSet > operator*() const;
        GModelVertexSetIterator& operator++();
        GModelVertexSetIterator operator++(int);
        bool operator==(const GModelVertexSetIterator& other) const;
        bool operator!=(const GModelVertexSetIterator& other) const;
};

class GModelVertexSet
{
    protected:
        const GStorageVertexSet& _vertex_set;

    public:
        typedef GStorageVertexSet::VertexIterator VertexIterator;

        GModelVertexSet(const GStorageVertexSet& vertex_set);
        GModelVertexSet(const GModelVertexSet& gmodel_vertex_set);

        const string& name() const;

        size_t vertexCount() const;

        VertexIterator beginVertexIterator() const;
        VertexIterator endVertexIterator() const;
};

class GModelArcSetIterator
{
    protected:
        map<size_t, GStorageArcSet>::const_iterator _iterator;

    public:
        GModelArcSetIterator(const GStorageDiGraph::ArcSetIterator& iterator);
        GModelArcSetIterator(const GModelArcSetIterator& other);

        pair< size_t, GModelArcSet > operator*() const;
        GModelArcSetIterator& operator++();
        GModelArcSetIterator operator++(int);
        bool operator==(const GModelArcSetIterator& other) const;
        bool operator!=(const GModelArcSetIterator& other) const;
};

class GModelArcSet
{
    protected:
        const GStorageArcSet& _arc_set;

    public:
        typedef GStorageArcSet::ArcIterator ArcIterator;

        GModelArcSet(const GStorageArcSet& arc_set);
        GModelArcSet(const GModelArcSet& gmodel_arc_set);

        const string& name() const;

        size_t arcCount() const;

        ArcIterator beginArcIterator() const;
        ArcIterator endArcIterator() const;
};

class GModelPathIterator
{
    protected:
        map<size_t, GStoragePath>::const_iterator _iterator;

    public:
        GModelPathIterator(const GStorageDiGraph::PathIterator& iterator);
        GModelPathIterator(const GModelPathIterator& other);

        pair< size_t, GModelPath > operator*() const;
        GModelPathIterator& operator++();
        GModelPathIterator operator++(int);
        bool operator==(const GModelPathIterator& other) const;
        bool operator!=(const GModelPathIterator& other) const;
};

class GModelPath
{
    protected:
        const GStoragePath& _path;

    public:
        typedef GStoragePath::VertexIterator VertexIterator;
        typedef GStoragePath::ArcIterator ArcIterator;

        GModelPath(const GStoragePath& path);
        GModelPath(const GModelPath& gmodel_path);

        const string& name() const;

        size_t length() const;

        VertexIterator beginVertexIterator() const;
        VertexIterator endVertexIterator() const;

        ArcIterator beginArcIterator() const;
        ArcIterator endArcIterator() const;
};

enum GModelMainSelectedType
{
    MainSelectedNone,
    MainSelectedDiGraph
};

union GModelMainSelectedID
{
    size_t digraph_id;
};

enum GModelSubSelectedType
{
    SubSelectedNone,
    SubSelectedVertex,
    SubSelectedArc,
    SubSelectedVertexSet,
    SubSelectedArcSet,
    SubSelectedPath
};

union GModelSubSelectedID
{
    size_t vertex_id;
    struct
    {
        size_t start;
        size_t end;
    } arc_id;
    size_t vertex_set_id;
    size_t arc_set_id;
    size_t path_id;
};

class GModel
{
    protected:
        GStorage& _gstorage;
        list<GView*> _gview_list;
        GModelMainSelectedType _main_selected_type;
        GModelMainSelectedID _main_selected_id;
        GModelSubSelectedType _sub_selected_type;
        GModelSubSelectedID _sub_selected_id;

        void notifyGView(int action, size_t first_id = 0, size_t second_id = 0);

        void createDiGraphPath(size_t digraph_id, const Path& path);
        void createDiGraphVertexSet(size_t digraph_id, const VertexSet& vertex_set);
        void createDiGraphArcSet(size_t digraph_id, const ArcSet& arc_set);

        void modifyDiGraphPath(size_t digraph_id, size_t path_id, const Path& path);
        void modifyDiGraphVertexSet(size_t digraph_id, size_t vertex_set_id, const VertexSet& vertex_set);
        void modifyDiGraphArcSet(size_t digraph_id, size_t arc_set_id, const ArcSet& arc_set);

    public:
        typedef GModelDiGraphIterator DiGraphIterator;

        GModel(GStorage& gstorage);
        GModel(const GModel& gmodel);
        ~GModel();

        void addGView(GView& gview);
        void removeGView(GView& gview);

        void createDiGraph();
        void destroyDiGraph(size_t digraph_id);

        void selectDiGraph(size_t digraph_id);
        void selectDiGraphVertex(size_t digraph_id, size_t vertex_id);
        void selectDiGraphArc(size_t digraph_id, size_t arc_start_id, size_t arc_end_id);
        void selectDiGraphVertexSet(size_t digraph_id, size_t vertex_set_id);
        void selectDiGraphArcSet(size_t digraph_id, size_t arc_set_id);
        void selectDiGraphPath(size_t digraph_id, size_t path_id);

        template< typename iterator >
        void createDiGraphVertexSet(size_t digraph_id, iterator first, iterator last, size_t size);

        template< typename iterator >
        void createDiGraphArcSet(size_t digraph_id, iterator first, iterator last, size_t size);

        template< typename iterator >
        void createDiGraphPath(size_t digraph_id, iterator first, iterator last, size_t size);

        template< typename iterator >
        void modifyDiGraphVertexSet(size_t digraph_id, size_t vertex_set_id, iterator first, iterator last, size_t size);

        template< typename iterator >
        void modifyDiGraphArcSet(size_t digraph_id, size_t arc_set_id, iterator first, iterator last, size_t size);

        template< typename iterator >
        void modifyDiGraphPath(size_t digraph_id, size_t path_id, iterator first, iterator last, size_t size);

        void destroyDiGraphVertexSet(size_t digraph_id, size_t vertex_set_id);
        void destroyDiGraphArcSet(size_t digraph_id, size_t arc_set_id);
        void destroyDiGraphPath(size_t digraph_id, size_t path_id);

        void addDiGraphVertex(size_t digraph_id);
        void removeDiGraphVertex(size_t digraph_id, size_t id);

        void addDiGraphArc(size_t digraph_id, size_t start_id, size_t end_id);
        void removeDiGraphArc(size_t digraph_id, size_t start_id, size_t end_id);

        void checkDiGraphIsWeaklyConnected(size_t digraph_id);
        void checkDiGraphIsStronglyConnected(size_t digraph_id);
        void checkDiGraphIsComplete(size_t digraph_id);
        void checkDiGraphIsSimple(size_t digraph_id);
        void checkDiGraphIsAcyclic(size_t digraph_id);
        void checkDiGraphIsTree(size_t digraph_id);

        void findDiGraphEulerianCycle(size_t digraph_id);
        void findDiGraphHamiltonianCycle(size_t digraph_id);
        void findDiGraphDecomposition(size_t digraph_id);

        void generateDiGraphReachabilityGraph(size_t digraph_id);
        void generateDiGraphSubgraph(size_t digraph_id, size_t vertex_set_id);
        void generateDiGraphPartialGraph(size_t digraph_id, size_t arc_set_id);

        GModelDiGraph getDiGraph(size_t digraph_id) const;

        DiGraphIterator beginDiGraphIterator() const;
        DiGraphIterator endDiGraphIterator() const;
};

template< typename iterator >
void GModel::createDiGraphPath(size_t digraph_id, iterator first, iterator last, size_t size)
{
    createDiGraphPath(digraph_id, Path(first, last));
}

template< typename iterator >
void GModel::createDiGraphVertexSet(size_t digraph_id, iterator first, iterator last, size_t size)
{
    createDiGraphVertexSet(digraph_id, VertexSet(first, last, size));
}

template< typename iterator >
void GModel::createDiGraphArcSet(size_t digraph_id, iterator first, iterator last, size_t size)
{
    createDiGraphArcSet(digraph_id, ArcSet(first, last, size));
}

template< typename iterator >
void GModel::modifyDiGraphPath(size_t digraph_id, size_t path_id, iterator first, iterator last, size_t size)
{
    modifyDiGraphPath(digraph_id, path_id, Path(first, last));
}

template< typename iterator >
void GModel::modifyDiGraphVertexSet(size_t digraph_id, size_t vertex_set_id, iterator first, iterator last, size_t size)
{
    modifyDiGraphVertexSet(digraph_id, vertex_set_id, VertexSet(first, last, size));
}

template< typename iterator >
void GModel::modifyDiGraphArcSet(size_t digraph_id, size_t arc_set_id, iterator first, iterator last, size_t size)
{
    modifyDiGraphArcSet(digraph_id, arc_set_id, ArcSet(first, last, size));
}

#endif // GMODEL_H
