#include "Matter.h"
#include <app/server/OnboardingCodesUtil.h>
using namespace chip;
using namespace chip::app::Clusters;
using namespace esp_matter;
using namespace esp_matter::endpoint;

/**
 * This program presents example Matter plugin unit (switch) device with two endpoints 
 * with OnOff clusters by controlling LEDs with Matter and toggle buttons.
 *
 * You can toggle plugin unit by both:
 *  - Matter (via CHIPTool or other Matter controller)
 *  - toggle button (with debouncing)
 */

// Please configure your PINs
const int LED_PIN_1 = 2;
const int LED_PIN_2 = 17;
const int TOGGLE_BUTTON_PIN_1 = 0;
const int TOGGLE_BUTTON_PIN_2 = 21;

// Debounce for toggle button
const int DEBOUNCE_DELAY = 500;
int last_toggle;

// Cluster and attribute ID used by Matter plugin unit device
const uint32_t CLUSTER_ID = OnOff::Id;
const uint32_t ATTRIBUTE_ID = OnOff::Attributes::OnOff::Id;

// Endpoint and attribute ref that will be assigned to Matter device
uint16_t plugin_unit_endpoint_id_1 = 0;
uint16_t plugin_unit_endpoint_id_2 = 0;
attribute_t *attribute_ref_1;
attribute_t *attribute_ref_2;

// There is possibility to listen for various device events, related for example
// to setup process. Leaved as empty for simplicity.
static void on_device_event(const ChipDeviceEvent *event, intptr_t arg) {}
static esp_err_t on_identification(identification::callback_type_t type,
                                   uint16_t endpoint_id, uint8_t effect_id,
                                   void *priv_data) {
  return ESP_OK;
}

// Listener on attribute update requests.
// In this example, when update is requested, path (endpoint, cluster and
// attribute) is checked if it matches plugin unit attribute. If yes, LED changes
// state to new one.
static esp_err_t on_attribute_update(attribute::callback_type_t type,
                                     uint16_t endpoint_id, uint32_t cluster_id,
                                     uint32_t attribute_id,
                                     esp_matter_attr_val_t *val,
                                     void *priv_data) {
  if (type == attribute::PRE_UPDATE && cluster_id == CLUSTER_ID && attribute_id == ATTRIBUTE_ID) {
    // We got an plugin unit on/off attribute update!
    boolean new_state = val->val.b;
    if (endpoint_id == plugin_unit_endpoint_id_1) {
      digitalWrite(LED_PIN_1, new_state);
    } else if (endpoint_id == plugin_unit_endpoint_id_2) {
      digitalWrite(LED_PIN_2, new_state);
    }
  }
  return ESP_OK;
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(TOGGLE_BUTTON_PIN_1, INPUT);
  pinMode(TOGGLE_BUTTON_PIN_2, INPUT);

  // Enable debug logging
  esp_log_level_set("*", ESP_LOG_DEBUG);

  // Setup Matter node
  node::config_t node_config;
  node_t *node =
    node::create(&node_config, on_attribute_update, on_identification);

  // Setup Plugin unit endpoint / cluster / attributes with default values
  on_off_plugin_unit::config_t plugin_unit_config;
  plugin_unit_config.on_off.on_off = false;
  plugin_unit_config.on_off.lighting.start_up_on_off = false;
  endpoint_t *endpoint_1 = on_off_plugin_unit::create(node, &plugin_unit_config,
                                                      ENDPOINT_FLAG_NONE, NULL);
  endpoint_t *endpoint_2 = on_off_plugin_unit::create(node, &plugin_unit_config,
                                                      ENDPOINT_FLAG_NONE, NULL);

  // Save on/off attribute reference. It will be used to read attribute value later.
  attribute_ref_1 =
    attribute::get(cluster::get(endpoint_1, CLUSTER_ID), ATTRIBUTE_ID);
  attribute_ref_2 =
    attribute::get(cluster::get(endpoint_2, CLUSTER_ID), ATTRIBUTE_ID);

  // Save generated endpoint id
  plugin_unit_endpoint_id_1 = endpoint::get_id(endpoint_1);
  plugin_unit_endpoint_id_2 = endpoint::get_id(endpoint_2);

  // Start Matter device
  esp_matter::start(on_device_event);

  // Print codes needed to setup Matter device
  PrintOnboardingCodes(
    chip::RendezvousInformationFlags(chip::RendezvousInformationFlag::kBLE));
}

// Reads plugin unit on/off attribute value
esp_matter_attr_val_t get_onoff_attribute_value(esp_matter::attribute_t *attribute_ref) {
  esp_matter_attr_val_t onoff_value = esp_matter_invalid(NULL);
  attribute::get_val(attribute_ref, &onoff_value);
  return onoff_value;
}

// Sets plugin unit on/off attribute value
void set_onoff_attribute_value(esp_matter_attr_val_t *onoff_value, uint16_t plugin_unit_endpoint_id) {
  attribute::update(plugin_unit_endpoint_id, CLUSTER_ID, ATTRIBUTE_ID, onoff_value);
}

// When toggle plugin unit button is pressed (with debouncing),
// plugin unit attribute value is changed
void loop() {
  if ((millis() - last_toggle) > DEBOUNCE_DELAY) {
    if (!digitalRead(TOGGLE_BUTTON_PIN_1)) {
      last_toggle = millis();
      // Read actual on/off value, invert it and set
      esp_matter_attr_val_t onoff_value = get_onoff_attribute_value(attribute_ref_1);
      onoff_value.val.b = !onoff_value.val.b;
      set_onoff_attribute_value(&onoff_value, plugin_unit_endpoint_id_1);
    }

    if (!digitalRead(TOGGLE_BUTTON_PIN_2)) {
      last_toggle = millis();
      // Read actual on/off value, invert it and set
      esp_matter_attr_val_t onoff_value = get_onoff_attribute_value(attribute_ref_2);
      onoff_value.val.b = !onoff_value.val.b;
      set_onoff_attribute_value(&onoff_value, plugin_unit_endpoint_id_2);
    }
  }
}