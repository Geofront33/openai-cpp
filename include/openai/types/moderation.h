#pragma once
#include <openai/third_party/nlohmann/json.h>

namespace openai
{

struct Moderation
{
  struct Categories
  {
    bool harassment;
    bool harassment_threatening;
    bool hate;
    bool hate_threatening;
    std::optional<bool> illicit;
    std::optional<bool> illicit_violent;
    bool self_harm;
    bool self_harm_instructions;
    bool self_harm_intent;
    bool sexual;
    bool sexual_minors;
    bool violence;
    bool violence_graphic;

    std::string to_string() const;
  };

  struct CategoryAppliedInputTypes
  {
    std::vector<std::string> harassment;
    std::vector<std::string> harassment_threatening;
    std::vector<std::string> hate;
    std::vector<std::string> hate_threatening;
    std::vector<std::string> illicit;
    std::vector<std::string> illicit_violent;
    std::vector<std::string> self_harm;
    std::vector<std::string> self_harm_instructions;
    std::vector<std::string> self_harm_intent;
    std::vector<std::string> sexual;
    std::vector<std::string> sexual_minors;
    std::vector<std::string> violence;
    std::vector<std::string> violence_graphic;
  };

  struct CategoryScores
  {
    float harassment;
    float harassment_threatening;
    float hate;
    float hate_threatening;
    float illicit;
    float illicit_violent;
    float self_harm;
    float self_harm_instructions;
    float self_harm_intent;
    float sexual;
    float sexual_minors;
    float violence;
    float violence_graphic;
  };

  Categories categories;
  std::optional<CategoryAppliedInputTypes> category_applied_input_types;
  CategoryScores category_scores;
  bool flagged;
};

void from_json(const nlohmann::json& j, Moderation::Categories& x);
void from_json(const nlohmann::json& j, Moderation::CategoryAppliedInputTypes& x);
void from_json(const nlohmann::json& j, Moderation::CategoryScores& x);
void from_json(const nlohmann::json& j, Moderation& x);

}
