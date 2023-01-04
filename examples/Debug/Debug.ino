#include "Matter.h"
#include <app/server/OnboardingCodesUtil.h>
using namespace chip;
using namespace chip::app::Clusters;
using namespace esp_matter;
using namespace esp_matter::endpoint;

/**
   This program presents many Matter devices and should be used only
   for debug purposes (for example checking which devices types are supported
   in Matter controller).

   Keep in mind that it IS NOT POSSIBLE to run all those endpoints due to
   out of memory. There is need to manually comment out endpoints!
   Running about 4 endpoints at the same time should work.
*/

static void on_device_event(const ChipDeviceEvent *event, intptr_t arg) {}
static esp_err_t on_identification(identification::callback_type_t type, uint16_t endpoint_id,
                                   uint8_t effect_id, void *priv_data) {
  return ESP_OK;
}

static esp_err_t on_attribute_update(attribute::callback_type_t type, uint16_t endpoint_id, uint32_t cluster_id,
                                     uint32_t attribute_id, esp_matter_attr_val_t *val, void *priv_data) {
  if (type == attribute::PRE_UPDATE) {
    Serial.print("Update on endpoint: ");
    Serial.print(endpoint_id);
    Serial.print(" cluster: ");
    Serial.print(cluster_id);
    Serial.print(" attribute: ");
    Serial.println(attribute_id);
  }
  return ESP_OK;
}

void print_endpoint_info(String clusterName, endpoint_t *endpoint) {
  uint16_t endpoint_id = endpoint::get_id(endpoint);
  Serial.print(clusterName);
  Serial.print(" has endpoint: ");
  Serial.println(endpoint_id);
}

void setup() {
  Serial.begin(115200);

  esp_log_level_set("*", ESP_LOG_DEBUG);

  node::config_t node_config;
  node_t *node = node::create(&node_config, on_attribute_update, on_identification);

  endpoint_t *endpoint;
  cluster_t *cluster;

  // !!!
  // USE ONLY ABOUT 4 ENDPOINTS TO AVOID OUT OF MEMORY ERRORS
  // MANUALLY COMMENT REST OF ENDPOINTS
  // !!!
  
  on_off_light::config_t light_config;
  endpoint = on_off_light::create(node, &light_config, ENDPOINT_FLAG_NONE, NULL);
  print_endpoint_info("on_off_light", endpoint);
  
  dimmable_light::config_t dimmable_light_config;
  endpoint = dimmable_light::create(node, &dimmable_light_config, ENDPOINT_FLAG_NONE, NULL);
  print_endpoint_info("dimmable_light", endpoint);

  color_temperature_light::config_t color_temperature_light_config;
  endpoint = color_temperature_light::create(node, &color_temperature_light_config, ENDPOINT_FLAG_NONE, NULL);
  /* Add color control cluster */
  cluster = cluster::get(endpoint, ColorControl::Id);
  cluster::color_control::feature::hue_saturation::config_t hue_saturation_config;
  cluster::color_control::feature::hue_saturation::add(cluster, &hue_saturation_config);
  print_endpoint_info("color_temperature_light", endpoint);

  extended_color_light::config_t extended_color_light_config;
  endpoint = extended_color_light::create(node, &extended_color_light_config, ENDPOINT_FLAG_NONE, NULL);
  print_endpoint_info("extended_color_light", endpoint);

  generic_switch::config_t generic_switch_config;
  generic_switch_config.switch_cluster.current_position = 1;
  generic_switch_config.switch_cluster.number_of_positions = 3;  
  endpoint = generic_switch::create(node, &generic_switch_config, ENDPOINT_FLAG_NONE, NULL);
  print_endpoint_info("generic_switch", endpoint);

  on_off_plugin_unit::config_t on_off_plugin_unit_config;
  on_off_plugin_unit_config.on_off.on_off = true;
  endpoint = on_off_plugin_unit::create(node, &on_off_plugin_unit_config, ENDPOINT_FLAG_NONE, NULL);
  print_endpoint_info("on_off_plugin_unit", endpoint);

  dimmable_plugin_unit::config_t dimmable_plugin_unit_config;
  endpoint = dimmable_plugin_unit::create(node, &dimmable_plugin_unit_config, ENDPOINT_FLAG_NONE, NULL);
  print_endpoint_info("dimmable_plugin_unit", endpoint);

  fan::config_t fan_config;
  endpoint = fan::create(node, &fan_config, ENDPOINT_FLAG_NONE, NULL);
  print_endpoint_info("fan", endpoint);

  thermostat::config_t thermostat_config;
  thermostat_config.thermostat.local_temperature = 19;
  endpoint = thermostat::create(node, &thermostat_config, ENDPOINT_FLAG_NONE, NULL);
  print_endpoint_info("thermostat", endpoint);

  door_lock::config_t door_lock_config;
  door_lock_config.door_lock.lock_state = 1;
  endpoint = door_lock::create(node, &door_lock_config, ENDPOINT_FLAG_NONE, NULL);
  print_endpoint_info("door_lock", endpoint);

  window_covering_device::config_t window_covering_device_config;
  endpoint = window_covering_device::create(node, &window_covering_device_config, ENDPOINT_FLAG_NONE, NULL);
  /* Add additional control clusters */
  cluster = cluster::get(endpoint, WindowCovering::Id);
  cluster::window_covering::feature::lift::config_t lift;
  cluster::window_covering::feature::tilt::config_t tilt;
  cluster::window_covering::feature::position_aware_lift::config_t position_aware_lift;
  cluster::window_covering::feature::position_aware_tilt::config_t position_aware_tilt;
  cluster::window_covering::feature::absolute_position::config_t absolute_position;
  cluster::window_covering::feature::lift::add(cluster, &lift);
  cluster::window_covering::feature::tilt::add(cluster, &tilt);
  cluster::window_covering::feature::position_aware_lift::add(cluster, &position_aware_lift);
  cluster::window_covering::feature::position_aware_tilt::add(cluster, &position_aware_tilt);
  cluster::window_covering::feature::absolute_position::add(cluster, &absolute_position);
  print_endpoint_info("window_covering_device", endpoint);

  temperature_sensor::config_t temperature_sensor_config;
  temperature_sensor_config.temperature_measurement.measured_value = 22;
  endpoint = temperature_sensor::create(node, &temperature_sensor_config, ENDPOINT_FLAG_NONE, NULL);
  print_endpoint_info("temperature_sensor", endpoint);

  occupancy_sensor::config_t occupancy_sensor_config;
  occupancy_sensor_config.occupancy_sensing.occupancy = 1;
  endpoint = occupancy_sensor::create(node, &occupancy_sensor_config, ENDPOINT_FLAG_NONE, NULL);
  print_endpoint_info("occupancy_sensor", endpoint);

  contact_sensor::config_t contact_sensor_config;
  contact_sensor_config.boolean_state.state_value = true;
  endpoint = contact_sensor::create(node, &contact_sensor_config, ENDPOINT_FLAG_NONE, NULL);
  print_endpoint_info("contact_sensor", endpoint);

  esp_matter::start(on_device_event);

  PrintOnboardingCodes(chip::RendezvousInformationFlags(chip::RendezvousInformationFlag::kBLE));
}

void loop() {

}