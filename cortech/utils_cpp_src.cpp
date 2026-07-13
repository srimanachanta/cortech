#include <vector>
#include <unordered_map>

/*
Map the values in `values` from `source` to the corresponding values in `target`.
*/
std::vector<int> map_values_from_source_to_target(
    std::vector<int> source_values,
    std::vector<int> target_values,
    std::vector<int> values)
{
    // build map
    std::unordered_map<int, int> map(source_values.size());
    for (std::size_t i = 0; i < source_values.size(); ++i)
        map[source_values[i]] = target_values[i];
    // apply map
    std::vector<int> values_out(values.size());
    for (std::size_t i = 0; i < values.size(); ++i)
        values_out[i] = map.at(values[i]);
    return values_out;
}