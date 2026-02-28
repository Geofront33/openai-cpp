#include <openai/types/moderation.h>
#include <openai/utils/utils.h>

namespace openai
{

std::string Moderation::Categories::to_string() const {
  std::ostringstream oss;
  oss << "Categories(harassment=" << harassment;
  oss << ", harassment/threatening=" << harassment_threatening;
  oss << ", hate=" << hate;
  oss << ", hate/threatening=" << hate_threatening;
  if (illicit) oss << ", illicit=" << *illicit;
  if (illicit_violent) oss << ", illicit/violent=" << *illicit;
  oss << ", self-harm=" << self_harm;
  oss << ", self-harm/instructions=" << self_harm_instructions;
  oss << ", self-harm/intent=" << self_harm_intent;
  oss << ", sexual=" << sexual;
  oss << ", sexual/minors=" << sexual_minors;
  oss << ", violence=" << violence;
  oss << ", violence/graphic=" << violence_graphic;
  oss << ")";
  return oss.str();
}

void from_json(const nlohmann::json& j, Moderation::Categories& x) {
  j.at("harassment").get_to(x.harassment);
  j.at("harassment/threatening").get_to(x.harassment_threatening);
  j.at("hate").get_to(x.hate);
  j.at("hate/threatening").get_to(x.hate_threatening);
  get_opt(j, "illicit", x.illicit);
  get_opt(j, "illicit/violent", x.illicit_violent);
  j.at("self-harm").get_to(x.self_harm);
  j.at("self-harm/instructions").get_to(x.self_harm_instructions);
  j.at("self-harm/intent").get_to(x.self_harm_intent);
  j.at("sexual").get_to(x.sexual);
  j.at("sexual/minors").get_to(x.sexual_minors);
  j.at("violence").get_to(x.violence);
  j.at("violence/graphic").get_to(x.violence_graphic);
}

void from_json(const nlohmann::json& j, Moderation::CategoryAppliedInputTypes& x) {
  j.at("harassment").get_to(x.harassment);
  j.at("harassment/threatening").get_to(x.harassment_threatening);
  j.at("hate").get_to(x.hate);
  j.at("hate/threatening").get_to(x.hate_threatening);
  j.at("illicit").get_to(x.illicit);
  j.at("illicit/violent").get_to(x.illicit_violent);
  j.at("self-harm").get_to(x.self_harm);
  j.at("self-harm/instructions").get_to(x.self_harm_instructions);
  j.at("self-harm/intent").get_to(x.self_harm_intent);
  j.at("sexual").get_to(x.sexual);
  j.at("sexual/minors").get_to(x.sexual_minors);
  j.at("violence").get_to(x.violence);
  j.at("violence/graphic").get_to(x.violence_graphic);
}

void from_json(const nlohmann::json& j, Moderation::CategoryScores& x) {
  j.at("harassment").get_to(x.harassment);
  j.at("harassment/threatening").get_to(x.harassment_threatening);
  j.at("hate").get_to(x.hate);
  j.at("hate/threatening").get_to(x.hate_threatening);
  j.at("illicit").get_to(x.illicit);
  j.at("illicit/violent").get_to(x.illicit_violent);
  j.at("self-harm").get_to(x.self_harm);
  j.at("self-harm/instructions").get_to(x.self_harm_instructions);
  j.at("self-harm/intent").get_to(x.self_harm_intent);
  j.at("sexual").get_to(x.sexual);
  j.at("sexual/minors").get_to(x.sexual_minors);
  j.at("violence").get_to(x.violence);
  j.at("violence/graphic").get_to(x.violence_graphic);
}

void from_json(const nlohmann::json& j, Moderation& x) {
  j.at("categories").get_to(x.categories);
  get_opt(j, "category_applied_input_types", x.category_applied_input_types);
  j.at("category_scores").get_to(x.category_scores);
  j.at("flagged").get_to(x.flagged);
}

}

