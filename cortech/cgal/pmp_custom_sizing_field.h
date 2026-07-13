// This is a modified version of Uniform_sizing CGAL Polygon mesh processing

#include <cmath>

#include <CGAL/license/Polygon_mesh_processing/meshing_hole_filling.h>
#include <CGAL/Polygon_mesh_processing/internal/Sizing_field_base.h>
#include <CGAL/number_utils.h>

namespace CGAL
{
namespace Polygon_mesh_processing
{
/*!
* \ingroup PMP_local_remeshing_grp
*
* A sizing field describing a uniform target edge length for
* `CGAL::Polygon_mesh_processing::isotropic_remeshing()`.
*
* Edges are never split
* Edges shorter than the target edge length will be collapsed
*
* \cgalModels{PMPSizingField}
*
* \sa `isotropic_remeshing()`
* \sa `Adaptive_sizing_field`
*
* @tparam PolygonMesh model of `MutableFaceGraph` that
*         has an internal property map for `CGAL::vertex_point_t`.
* @tparam VPMap property map associating points to the vertices of `pmesh`,
*         model of `ReadWritePropertyMap` with `boost::graph_traits<PolygonMesh>::%vertex_descriptor`
*         as key type and `%Point_3` as value type. Default is `boost::get(CGAL::vertex_point, pmesh)`.
*/
template <class PolygonMesh,
          class VPMap =  typename boost::property_map<PolygonMesh, CGAL::vertex_point_t>::const_type>
class Uniform_sizing_field_strict_short
#ifndef DOXYGEN_RUNNING
: public internal::Sizing_field_base<PolygonMesh, VPMap>
#endif
{
private:
  typedef internal::Sizing_field_base<PolygonMesh, VPMap> Base;

public:
  typedef typename Base::FT         FT;
  typedef typename Base::Point_3    Point_3;
  typedef typename Base::halfedge_descriptor halfedge_descriptor;
  typedef typename Base::vertex_descriptor   vertex_descriptor;

  /// \name Creation
  /// @{

  /*!
  * Constructor.
  * \param size the target edge length for isotropic remeshing. If set to 0,
  *        the criterion for edge length is ignored and edges are neither split nor collapsed.
  * \param vpmap is the input vertex point map that associates points to the vertices of
  *        the input mesh.
  */
  Uniform_sizing_field_strict_short(const FT size, const VPMap& vpmap)
    : m_size(size)
    , m_sq_short(CGAL::square(1.0 * size))
    // , m_sq_long(  CGAL::square(4./3. * size))
    , m_sq_long(  CGAL::square(INFINITY))
    , m_vpmap(vpmap)
  {}

  /*!
  * Constructor using internal vertex point map of the input polygon mesh.
  *
  * @param size the target edge length for isotropic remeshing. If set to 0,
  *        the criterion for edge length is ignored and edges are neither split nor collapsed.
  * @param pmesh a polygon mesh with triangulated surface patches to be remeshed. The default
  *        vertex point map of `pmesh` is used to construct the class.
  */
  Uniform_sizing_field_strict_short(const FT size, const PolygonMesh& pmesh)
    : Uniform_sizing_field_strict_short(size, get(CGAL::vertex_point, pmesh))
  {}

  /// @}

private:
  FT sqlength(const vertex_descriptor va,
              const vertex_descriptor vb) const
  {
    return FT(squared_distance(get(m_vpmap, va), get(m_vpmap, vb)));
  }

  FT sqlength(const halfedge_descriptor& h, const PolygonMesh& pmesh) const
  {
    return sqlength(target(h, pmesh), source(h, pmesh));
  }

public:
  FT at(const vertex_descriptor /* v */, const PolygonMesh& /* pmesh */) const
  {
    return m_size;
  }

  std::optional<FT> is_too_long(const vertex_descriptor va, const vertex_descriptor vb, const PolygonMesh& /* pmesh */) const
  {
    return std::nullopt; // never too long
  }

  std::optional<FT> is_too_short(const halfedge_descriptor h, const PolygonMesh& pmesh) const
  {
    const FT sqlen = sqlength(h, pmesh);
    if (sqlen < m_sq_short)
      //no need to return the ratio for the uniform field
      return sqlen;
    else
      return std::nullopt;
  }

  Point_3 split_placement(const halfedge_descriptor h, const PolygonMesh& pmesh) const
  {
    return midpoint(get(m_vpmap, target(h, pmesh)),
                    get(m_vpmap, source(h, pmesh)));
  }

  void register_split_vertex(const vertex_descriptor /* v */, const PolygonMesh& /* pmesh */)
  {}

private:
  const FT m_size;
  const FT m_sq_short;
  const FT m_sq_long;
  const VPMap m_vpmap;
};

}//end namespace Polygon_mesh_processing
}//end namespace CGAL