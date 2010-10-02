#include "GModel.h"

GModelState::GModelState(GStorage& gstorage) : _gstorage(gstorage), _selected(GModelStateSelected::None)
{
}

void GModelState::selectDiGraph(size_t id)
{
    if (_selected == GModelStateSelected::DiGraph && _id == id) return;

    if (!_gstorage.hasDiGraph(id))
    {
        throw invalid_argument("FAIL");
    }
    clear();

    _selected = GModelStateSelected::DiGraph;
    _id = id;
}

void GModelState::selectDiGraphVertex(size_t id)
{
    if (_selected != GModelStateSelected::DiGraph) return;

    if (_selected_digraph == GModelStateDiGraphSelected::Vertex)
    {
        if (_vertex_list.front().first == id) return;
    }

    if (!_gstorage.getDiGraph(_id).getDiGraph().hasVertex(id))
    {
        throw invalid_argument("Fail2");
    }
    clearDiGraph();

    _selected_digraph = GModelStateDiGraphSelected::Vertex;
    _vertex_list.push_back(pair< vertex_t, AppendMode >(id, AppendModeUnion));

    _vertex_view.insert(pair< vertex_t, size_t >(id, 1));
}

void GModelState::selectDiGraphArc(size_t start_id, size_t end_id)
{
    if (_selected != GModelStateSelected::DiGraph) return;
    
    if (_selected_digraph == GModelStateDiGraphSelected::Arc)
    {
        if (_arc_list.front().first == arc_t(start_id, end_id)) return;
    }

    if (!_gstorage.getDiGraph(_id).getDiGraph().hasArc(start_id, end_id))
    {
        throw invalid_argument("Fail2");
    }
    clearDiGraph();

    _selected_digraph = GModelStateDiGraphSelected::Arc;
    _arc_list.push_back(pair< arc_t, AppendMode >(arc_t(start_id, end_id), AppendModeUnion));

    _arc_view.insert(pair< arc_t, size_t >(arc_t(start_id, end_id), 1));
}

void GModelState::selectDiGraphVertexSet(size_t id)
{
    if (_selected != GModelStateSelected::DiGraph) return;

    if (_selected_digraph == GModelStateDiGraphSelected::VertexSet)
    {
        if (_vertex_set_list.front() == id) return;
    }
    const VertexSet& vertex_set = _gstorage.getDiGraph(_id).getVertexSet(id).getVertexSet();

    clearDiGraph();
    _selected_digraph = GModelStateDiGraphSelected::VertexSet;
    _vertex_set_list.push_back(id);

    VertexSet::VertexIterator iterator = vertex_set.beginVertexIterator();
    VertexSet::VertexIterator end_iterator = vertex_set.endVertexIterator();

    for (; iterator != end_iterator; ++iterator)
    {
        _vertex_view.insert(pair< vertex_t, size_t >(*iterator, 1));
    }
}

void GModelState::selectDiGraphArcSet(size_t id)
{
    if (_selected != GModelStateSelected::DiGraph) return;

    if (_selected_digraph == GModelStateDiGraphSelected::ArcSet)
    {
        if (_arc_set_list.front() == id) return;
    }
    const ArcSet& arc_set = _gstorage.getDiGraph(_id).getArcSet(id).getArcSet();

    clearDiGraph();
    _selected_digraph = GModelStateDiGraphSelected::ArcSet;
    _arc_set_list.push_back(id);

    ArcSet::ArcIterator iterator = arc_set.beginArcIterator();
    ArcSet::ArcIterator end_iterator = arc_set.endArcIterator();

    for (; iterator != end_iterator; ++iterator)
    {
        _arc_view.insert(pair< arc_t, size_t >(*iterator, 1));
    }
}

void GModelState::selectDiGraphPath(size_t id)
{
    if (_selected != GModelStateSelected::DiGraph) return;

    if (_selected_digraph == GModelStateDiGraphSelected::Path)
    {
        if (_path_list.front() == id) return;
    }
    const Path& path = _gstorage.getDiGraph(_id).getPath(id).getPath();

    clearDiGraph();
    _selected_digraph = GModelStateDiGraphSelected::Path;
    _path_list.push_back(id);

    Path::ArcIterator iterator = path.beginArcIterator();
    Path::ArcIterator end_iterator  = path.endArcIterator();

    for (; iterator != end_iterator; ++iterator)
    {
        const arc_t& arc = *iterator;
        _vertex_view.insert(pair< vertex_t, size_t >(arc.first, 1));
        _vertex_view.insert(pair< vertex_t, size_t >(arc.second, 1));
        _arc_view.insert(pair< arc_t, size_t >(arc, 1));
    }
}


void GModelState::selectAddDiGraphVertex(size_t id)
{
    if (_selected != GModelStateSelected::DiGraph) return;
    if (_selected_digraph == GModelStateDiGraphSelected::None) return;

    if (_selected_digraph.value() & GModelStateDiGraphSelected::Arc ||
        _selected_digraph.value() & GModelStateDiGraphSelected::ArcSet) return;

    if (_selected_digraph.value() & GModelStateDiGraphSelected::VertexSet)
    {
        if (_selected_digraph.value() & GModelStateDiGraphSelected::VertexSetMulti) return;
    }
    else if (_selected_digraph.value() & GModelStateDiGraphSelected::Path)
    {
        if (_selected_digraph.value() & GModelStateDiGraphSelected::PathMulti) return;
    }
    else if (_selected_digraph.value() & GModelStateDiGraphSelected::Vertex)
    {
        _selected_digraph = _selected_digraph.value() | GModelStateDiGraphSelected::VertexMulti;
    }
}

/*
void GModelState::selectAddDiGraphArc(size_t start_id, size_t end_id);
void GModelState::selectAddDiGraphVertexSet(size_t id);
void GModelState::selectAddDiGraphArcSet(size_t id);
void GModelState::selectAddDiGraphPath(size_t id);

void GModelState::selectRemoveDiGraphVertex(size_t id);
void GModelState::selectRemoveDiGraphArc(size_t start_id, size_t end_id);
void GModelState::selectRemoveDiGraphVertexSet(size_t id);
void GModelState::selectRemoveDiGraphArcSet(size_t id);
void GModelState::selectRemoveDiGraphPath(size_t id);

void GModelState::save();
*/
void GModelState::clear()
{
    clearDiGraph();

    _selected = GModelStateSelected::None;
    _id = 0;
}

void GModelState::clearDiGraph()
{
    _selected_digraph = GModelStateDiGraphSelected::None;
    _vertex_view.clear();
    _arc_view.clear();
    _vertex_list.clear();
    _arc_list.clear();
    _vertex_set_list.clear();
    _arc_set_list.clear();
    _path_list.clear();
}

/*
void GModelState::createNewDiGraph(const string& name);
void GModelState::createNewDiGraphVertexSet(const string& name);
void GModelState::createNewDiGraphArcSet(const string& name);
void GModelState::createNewDiGraphPath(const string& name);

GModelStateSelected GModelState::typeSelected() const;
GModelStateDiGraphSelected GModelState::typeDiGraphSelected() const;

size_t GModelState::countDiGraphVertexSelected(size_t id) const;
size_t GModelState::countDiGraphArcSelected(size_t start_id, size_t end_id) const;

bool GModelState::isDiGraphVertexSetSelected(size_t id) const;
bool GModelState::isDiGraphArcSetSelected(size_t id) const;
bool GModelState::isDiGraphPathSelected(size_t id) const;
*/






GModelDiGraphIterator::GModelDiGraphIterator(const map<size_t, GStorageDiGraph>::const_iterator& iterator) :
                                             _iterator(iterator)
{
}

GModelDiGraphIterator::GModelDiGraphIterator(const GModelDiGraphIterator& other) :
                                             _iterator(other._iterator)
{
}

pair< size_t, GModelDiGraph > GModelDiGraphIterator::operator*() const
{
    return pair< size_t, GModelDiGraph >(_iterator->first, GModelDiGraph(_iterator->second));
}

GModelDiGraphIterator& GModelDiGraphIterator::operator++()
{
    ++_iterator;
    return *this;
}

GModelDiGraphIterator GModelDiGraphIterator::operator++(int)
{
    GModelDiGraphIterator temp(*this);
    ++_iterator;
    return temp;
}

bool GModelDiGraphIterator::operator==(const GModelDiGraphIterator& other) const
{
    return _iterator == other._iterator;
}

bool GModelDiGraphIterator::operator!=(const GModelDiGraphIterator& other) const
{
    return _iterator != other._iterator;
}

GModelDiGraph::GModelDiGraph(const GStorageDiGraph& gstorage_digraph) :
                             _gstorage_digraph(gstorage_digraph)
{
}

GModelDiGraph::GModelDiGraph(const GModelDiGraph& other) :
                             _gstorage_digraph(other._gstorage_digraph)
{
}

const string& GModelDiGraph::name() const
{
    return _gstorage_digraph.getName();
}

size_t GModelDiGraph::vertexCount() const
{
    return _gstorage_digraph.getDiGraph().vertexCount();
}

size_t GModelDiGraph::arcCount() const
{
    return _gstorage_digraph.getDiGraph().arcCount();
}

GModelDiGraphProperties GModelDiGraph::getProperties() const
{
    return GModelDiGraphProperties(_gstorage_digraph.getDiGraph().getProperties());
}

GModelPath GModelDiGraph::getPath(size_t id) const
{
    return GModelPath(_gstorage_digraph.getPath(id));
}

GModelVertexSet GModelDiGraph::getVertexSet(size_t id) const
{
    return GModelVertexSet(_gstorage_digraph.getVertexSet(id));
}

GModelArcSet GModelDiGraph::getArcSet(size_t id) const
{
    return GModelArcSet(_gstorage_digraph.getArcSet(id));
}

GModelDiGraph::VertexSetIterator GModelDiGraph::beginVertexSetIterator() const
{
    return GModelDiGraph::VertexSetIterator(_gstorage_digraph.beginVertexSetIterator());
}

GModelDiGraph::VertexSetIterator GModelDiGraph::endVertexSetIterator() const
{
    return GModelDiGraph::VertexSetIterator(_gstorage_digraph.endVertexSetIterator());
}

GModelDiGraph::ArcSetIterator GModelDiGraph::beginArcSetIterator() const
{
    return GModelDiGraph::ArcSetIterator(_gstorage_digraph.beginArcSetIterator());
}

GModelDiGraph::ArcSetIterator GModelDiGraph::endArcSetIterator() const
{
    return GModelDiGraph::ArcSetIterator(_gstorage_digraph.endArcSetIterator());
}

GModelDiGraph::PathIterator GModelDiGraph::beginPathIterator() const
{
    return GModelDiGraph::PathIterator(_gstorage_digraph.beginPathIterator());
}

GModelDiGraph::PathIterator GModelDiGraph::endPathIterator() const
{
    return GModelDiGraph::PathIterator(_gstorage_digraph.endPathIterator());
}

GModelDiGraphProperties::GModelDiGraphProperties(const GStorageDiGraph::Properties& digraph_properties) :
                                                 _properties(digraph_properties)
{
}

GModelDiGraphProperties::GModelDiGraphProperties(const GModelDiGraphProperties& other) :
                                                 _properties(other._properties)
{
}

bool GModelDiGraphProperties::isWeaklyConnectedDefined() const
{ return _properties.isWeaklyConnectedDefined; }

bool GModelDiGraphProperties::isStronglyConnectedDefined() const
{ return _properties.isStronglyConnectedDefined; }

bool GModelDiGraphProperties::isAcyclicDefined() const
{ return _properties.isAcyclicDefined; }

bool GModelDiGraphProperties::isCompleteDefined() const
{ return _properties.isCompleteDefined; }

bool GModelDiGraphProperties::isSimpleDefined() const
{ return _properties.isSimpleDefined; }

bool GModelDiGraphProperties::isTreeDefined() const
{ return _properties.isTreeDefined; }

bool GModelDiGraphProperties::isWeaklyConnected() const
{ return _properties.isWeaklyConnected; }

bool GModelDiGraphProperties::isStronglyConnected() const
{ return _properties.isStronglyConnected; }

bool GModelDiGraphProperties::isAcyclic() const
{ return _properties.isAcyclic; }

bool GModelDiGraphProperties::isComplete() const
{ return _properties.isComplete; }

bool GModelDiGraphProperties::isSimple() const
{ return _properties.isSimple; }

bool GModelDiGraphProperties::isTree() const
{ return _properties.isTree; }

GModelVertexSetIterator::GModelVertexSetIterator(const map<size_t, GStorageVertexSet>::const_iterator& iterator) :
                                                 _iterator(iterator)
{
}

GModelVertexSetIterator::GModelVertexSetIterator(const GModelVertexSetIterator& other) :
                                                 _iterator(other._iterator)
{
}

pair< size_t, GModelVertexSet > GModelVertexSetIterator::operator*() const
{
    return pair< size_t, GModelVertexSet >(_iterator->first, GModelVertexSet(_iterator->second));
}

GModelVertexSetIterator& GModelVertexSetIterator::operator++()
{
    ++_iterator;
    return *this;
}

GModelVertexSetIterator GModelVertexSetIterator::operator++(int)
{
    GModelVertexSetIterator temp(*this);
    ++_iterator;
    return temp;
}

bool GModelVertexSetIterator::operator==(const GModelVertexSetIterator& other) const
{
    return _iterator == other._iterator;
}

bool GModelVertexSetIterator::operator!=(const GModelVertexSetIterator& other) const
{
    return _iterator != other._iterator;
}

GModelVertexSet::GModelVertexSet(const GStorageVertexSet& vertex_set) : _vertex_set(vertex_set) { }

GModelVertexSet::GModelVertexSet(const GModelVertexSet& other) :
                                 _vertex_set(other._vertex_set) { }

const string& GModelVertexSet::name() const
{
    return _vertex_set.getName();
}

size_t GModelVertexSet::vertexCount() const
{
    return _vertex_set.getVertexSet().count();
}

GModelVertexSet::VertexIterator GModelVertexSet::beginVertexIterator() const
{
    return GModelVertexSet::VertexIterator(_vertex_set.getVertexSet().beginVertexIterator());
}

GModelVertexSet::VertexIterator GModelVertexSet::endVertexIterator() const
{
    return GModelVertexSet::VertexIterator(_vertex_set.getVertexSet().endVertexIterator());
}

GModelArcSetIterator::GModelArcSetIterator(const map<size_t, GStorageArcSet>::const_iterator& iterator) :
                                           _iterator(iterator) { }

GModelArcSetIterator::GModelArcSetIterator(const GModelArcSetIterator& other) :
                                           _iterator(other._iterator) { }

pair< size_t, GModelArcSet > GModelArcSetIterator::operator*() const
{
    return pair< size_t, GModelArcSet >(_iterator->first, GModelArcSet(_iterator->second));
}

GModelArcSetIterator& GModelArcSetIterator::operator++()
{
    ++_iterator;
    return *this;
}

GModelArcSetIterator GModelArcSetIterator::operator++(int)
{
    GModelArcSetIterator temp(*this);
    ++_iterator;
    return temp;
}

bool GModelArcSetIterator::operator==(const GModelArcSetIterator& other) const
{
    return _iterator == other._iterator;
}

bool GModelArcSetIterator::operator!=(const GModelArcSetIterator& other) const
{
    return _iterator != other._iterator;
}

GModelArcSet::GModelArcSet(const GStorageArcSet& arc_set) :  _arc_set(arc_set)
{
}

GModelArcSet::GModelArcSet(const GModelArcSet& gmodel_arc_set) : _arc_set(gmodel_arc_set._arc_set)
{
}

const string& GModelArcSet::name() const
{
    return _arc_set.getName();
}

size_t GModelArcSet::arcCount() const
{
    return _arc_set.getArcSet().count();
}

GModelArcSet::ArcIterator GModelArcSet::beginArcIterator() const
{
    return GModelArcSet::ArcIterator(_arc_set.getArcSet().beginArcIterator());
}

GModelArcSet::ArcIterator GModelArcSet::endArcIterator() const
{
    return GModelArcSet::ArcIterator(_arc_set.getArcSet().endArcIterator());
}

GModelPathIterator::GModelPathIterator(const map<size_t, GStoragePath>::const_iterator& iterator) :
                                       _iterator(iterator)
{
}

GModelPathIterator::GModelPathIterator(const GModelPathIterator& other) :
                                       _iterator(other._iterator)
{
}

pair< size_t, GModelPath > GModelPathIterator::operator*() const
{
    return pair< size_t, GModelPath >(_iterator->first, GModelPath(_iterator->second));
}

GModelPathIterator& GModelPathIterator::operator++()
{
    ++_iterator;
    return *this;
}

GModelPathIterator GModelPathIterator::operator++(int)
{
    GModelPathIterator temp(*this);
    ++_iterator;
    return temp;
}

bool GModelPathIterator::operator==(const GModelPathIterator& other) const
{
    return _iterator == other._iterator;
}

bool GModelPathIterator::operator!=(const GModelPathIterator& other) const
{
    return _iterator != other._iterator;
}

GModelPath::GModelPath(const GStoragePath& path) : _path(path) { }

GModelPath::GModelPath(const GModelPath& gmodel_path) : _path(gmodel_path._path) { }

const string& GModelPath::name() const
{
    return _path.getName();
}

size_t GModelPath::length() const
{
    return _path.getPath().length();
}

GModelPath::VertexIterator GModelPath::beginVertexIterator() const
{
    return GModelPath::VertexIterator(_path.getPath().beginVertexIterator());
}

GModelPath::VertexIterator GModelPath::endVertexIterator() const
{
    return GModelPath::VertexIterator(_path.getPath().endVertexIterator());
}

GModelPath::ArcIterator GModelPath::beginArcIterator() const
{
    return GModelPath::ArcIterator(_path.getPath().beginArcIterator());
}

GModelPath::ArcIterator GModelPath::endArcIterator() const
{
    return GModelPath::ArcIterator(_path.getPath().endArcIterator());
}





GModel::GModel(GStorage& gstorage) : _gstorage(gstorage), _gview_list()
{
}

GModel::GModel(const GModel& gmodel) : _gstorage(gmodel._gstorage), _gview_list(gmodel._gview_list)
{
}

GModel::~GModel()
{
}

void GModel::addGView(GView& gview)
{
    _gview_list.push_back(&gview);
}

void GModel::removeGView(GView& gview)
{
    _gview_list.remove(&gview);
}

void GModel::notifyGView(int action, size_t first_id, size_t second_id)
{
    list<GView*>::iterator iterator = _gview_list.begin();
    list<GView*>::iterator end_iterator = _gview_list.end();

    for (; iterator != end_iterator; ++iterator)
    {
        GView* gview = *iterator;
        gview->updateNotify(action, first_id, second_id);
    }
}

void GModel::createDiGraph()
{
    //size_t digraph_id =
    _gstorage.addDiGraph(GStorageDiGraph(DiGraph(), "FAIL"));

    notifyGView(GViewActionUpdateDiGraph);
}

void GModel::destroyDiGraph(size_t digraph_id)
{
    _gstorage.removeDiGraph(digraph_id);

    notifyGView(GViewActionUpdateDiGraph);
}

void GModel::selectDiGraph(size_t digraph_id)
{
    _main_selected_type = MainSelectedDiGraph;
    _main_selected_id.digraph_id = digraph_id;

    //notify
}

void GModel::selectDiGraphVertex(size_t digraph_id, size_t vertex_id)
{
    _main_selected_type = MainSelectedDiGraph;
    _main_selected_id.digraph_id = digraph_id;
    _sub_selected_type = SubSelectedVertex;
    _sub_selected_id.vertex_id = vertex_id;

    //notify
}

void GModel::selectDiGraphArc(size_t digraph_id, size_t arc_start_id, size_t arc_end_id)
{
    _main_selected_type = MainSelectedDiGraph;
    _main_selected_id.digraph_id = digraph_id;
    _sub_selected_type = SubSelectedArc;
    _sub_selected_id.arc_id.start = arc_start_id;
    _sub_selected_id.arc_id.end = arc_end_id;

    //notify
}

void GModel::selectDiGraphVertexSet(size_t digraph_id, size_t vertex_set_id)
{
    _main_selected_type = MainSelectedDiGraph;
    _main_selected_id.digraph_id = digraph_id;
    _sub_selected_type = SubSelectedVertexSet;
    _sub_selected_id.vertex_set_id = vertex_set_id;

    //notify
}

void GModel::selectDiGraphArcSet(size_t digraph_id, size_t arc_set_id)
{
    _main_selected_type = MainSelectedDiGraph;
    _main_selected_id.digraph_id = digraph_id;
    _sub_selected_type = SubSelectedArcSet;
    _sub_selected_id.arc_set_id = arc_set_id;

    //notify
}

void GModel::selectDiGraphPath(size_t digraph_id, size_t path_id)
{
    _main_selected_type = MainSelectedDiGraph;
    _main_selected_id.digraph_id = digraph_id;
    _sub_selected_type = SubSelectedPath;
    _sub_selected_id.path_id = path_id;

    //notify
}

void GModel::createDiGraphPath(size_t digraph_id, const Path& path)
{   
    //size_t path_id =
    _gstorage.getDiGraph(digraph_id).addPath(GStoragePath(path, "FAIL"));
}

void GModel::createDiGraphVertexSet(size_t digraph_id, const VertexSet& vertex_set)
{
//    size_t vertex_set_id =
    _gstorage.getDiGraph(digraph_id).addVertexSet(GStorageVertexSet(vertex_set, "FAIL"));
}

void GModel::createDiGraphArcSet(size_t digraph_id, const ArcSet& arc_set)
{
//    size_t arc_set_id =
    _gstorage.getDiGraph(digraph_id).addArcSet(GStorageArcSet(arc_set, "FAIL"));
}

void GModel::modifyDiGraphPath(size_t digraph_id, size_t path_id, const Path& path)
{
    _gstorage.getDiGraph(digraph_id).getPath(path_id).getPath() = Path(path);
}

void GModel::modifyDiGraphVertexSet(size_t digraph_id, size_t vertex_set_id, const VertexSet& vertex_set)
{
    _gstorage.getDiGraph(digraph_id).getVertexSet(vertex_set_id).getVertexSet() = VertexSet(vertex_set);
}

void GModel::modifyDiGraphArcSet(size_t digraph_id, size_t arc_set_id, const ArcSet& arc_set)
{
    _gstorage.getDiGraph(digraph_id).getArcSet(arc_set_id).getArcSet() = ArcSet(arc_set);
}

void GModel::destroyDiGraphPath(size_t digraph_id, size_t path_id)
{
    _gstorage.getDiGraph(digraph_id).removePath(path_id);
}

void GModel::destroyDiGraphVertexSet(size_t digraph_id, size_t vertex_set_id)
{
    _gstorage.getDiGraph(digraph_id).removeVertexSet(vertex_set_id);
}

void GModel::destroyDiGraphArcSet(size_t digraph_id, size_t arc_set_id)
{
    _gstorage.getDiGraph(digraph_id).removeArcSet(arc_set_id);
}

void GModel::addDiGraphVertex(size_t digraph_id)
{
    _gstorage.getDiGraph(digraph_id).getDiGraph().addVertex();
}

void GModel::removeDiGraphVertex(size_t digraph_id, size_t index)
{
    _gstorage.getDiGraph(digraph_id).getDiGraph().removeVertex(index);
}

void GModel::addDiGraphArc(size_t digraph_id, size_t start_index, size_t end_index)
{
    _gstorage.getDiGraph(digraph_id).getDiGraph().addArc(start_index, end_index);
}

void GModel::removeDiGraphArc(size_t digraph_id, size_t start_index, size_t end_index)
{
    _gstorage.getDiGraph(digraph_id).getDiGraph().removeArc(start_index, end_index);
}

void GModel::findDiGraphEulerianCycle(size_t digraph_id)
{
    Path path = _gstorage.getDiGraph(digraph_id).getDiGraph().getEulerianCycle();

//  size_t path_id =
    _gstorage.getDiGraph(digraph_id).addPath(GStoragePath(path, "FAIL"));
}

void GModel::findDiGraphHamiltonianCycle(size_t digraph_id)
{
    Path path = _gstorage.getDiGraph(digraph_id).getDiGraph().getHamiltonianCycle();

//  size_t path_id =
    _gstorage.getDiGraph(digraph_id).addPath(GStoragePath(path, "FAIL"));
}

void GModel::findDiGraphDecomposition(size_t digraph_id)
{
    pair<DiGraph, DiGraph> decomposition = _gstorage.getDiGraph(digraph_id).getDiGraph().getDecomposition();

//    size_t first_digraph_id =
    _gstorage.addDiGraph(GStorageDiGraph(decomposition.first, "FAIL"));
//    size_t second_digraph_id =
    _gstorage.addDiGraph(GStorageDiGraph(decomposition.second, "FAIL"));
}

void GModel::generateDiGraphReachabilityGraph(size_t digraph_id)
{
    DiGraph reachability_graph = _gstorage.getDiGraph(digraph_id).getDiGraph().getReachabilityGraph();

//    size_t reachability_graph_id =
    _gstorage.addDiGraph(GStorageDiGraph(reachability_graph, "FAIL"));
}

void GModel::generateDiGraphSubgraph(size_t digraph_id, size_t vertex_set_id)
{
    const GStorageDiGraph& gstorage_digraph = _gstorage.getDiGraph(digraph_id);
    const GStorageVertexSet& vertex_set = gstorage_digraph.getVertexSet(vertex_set_id);

    DiGraph subgraph = gstorage_digraph.getDiGraph().getSubgraph(vertex_set.getVertexSet());

//    size_t subgraph_id =
    _gstorage.addDiGraph(GStorageDiGraph(subgraph, "FAIL"));
}

void GModel::generateDiGraphPartialGraph(size_t digraph_id, size_t arc_set_id)
{
    const GStorageDiGraph& gstorage_digraph = _gstorage.getDiGraph(digraph_id);
    const GStorageArcSet& arc_set = gstorage_digraph.getArcSet(arc_set_id);

    DiGraph partial_graph = gstorage_digraph.getDiGraph().getPartialGraph(arc_set.getArcSet());

//    size_t partial_graph_id =
    _gstorage.addDiGraph(GStorageDiGraph(partial_graph, "FAIL"));
}

GModelDiGraph GModel::getDiGraph(size_t digraph_id) const
{
    return GModelDiGraph(_gstorage.getDiGraph(digraph_id));
}

GModel::DiGraphIterator GModel::beginDiGraphIterator() const
{
    return GModel::DiGraphIterator(_gstorage.beginDiGraphIterator());
}

GModel::DiGraphIterator GModel::endDiGraphIterator() const
{
    return GModel::DiGraphIterator(_gstorage.endDiGraphIterator());
}
