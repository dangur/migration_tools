<?php

/**
 * @file
 * Defines migration classes for USAO organization.
 */
class UsaoDistrictMigration extends JusticeCsvMigration {
  public function __construct($arguments) {
    ini_set('auto_detect_line_endings', TRUE);

    $source_file = __DIR__ . '/../sources/usao-districts.csv';
    parent::__construct($arguments, $source_file);
    $this->dependencies = array('Organization');
    $this->description = t('Migrates USAO districts into organizations.');

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'abbreviation' => array('type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'Title',
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );
    $this->destination = new MigrateDestinationNode('organization');

    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('field_org_abbreviation', 'abbreviation');
    $this->addFieldMapping('migrate_redirects', 'abbreviation');
    $this->addFieldMapping('field_org_type')->defaultValue('district');
    $this->addFieldMapping('og_group_ref')->defaultValue('usao')->sourceMigration('Organization');

    // @todo set path to usao/districts/[abbreviation].
  }

  function csvcolumns() {
    // Note: Remember to subtract 1 from column number.
    $columns[0] = array('abbreviation', 'Abbreviation');
    $columns[1] = array('title', 'Title');
    $columns[2] = array('attorney', 'Attorney');

    return $columns;
  }

  function fields() {
    return array(
      'title' => 'The title',
      'abbreviation' => 'The organization abbreviation',
      'attorney' => 'The District Attorney',
    );
  }

  function prepareRow($row) {}
}

class UsaoStaffProfileMigration extends JusticeCsvMigration {
  public function __construct($arguments) {
    ini_set('auto_detect_line_endings', TRUE);

    $source_file = __DIR__ . '/../sources/usao-districts.csv';
    parent::__construct($arguments, $source_file);
    $this->dependencies = array('UsaoDistrict');
    $this->description = t('Migrates USAO District Attorneys.');

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'abbreviation' => array('type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'Title',
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );
    $this->destination = new MigrateDestinationNode('staff_profile');
    $this->addFieldMapping('title', 'attorney');
    $this->addFieldMapping('og_group_ref', 'abbreviation')->sourceMigration('UsaoDistrict');
  }

  function csvcolumns() {
    // Note: Remember to subtract 1 from column number.
    $columns[0] = array('abbreviation', 'Abbreviation');
    $columns[1] = array('title', 'Title');
    $columns[2] = array('attorney', 'Attorney');

    return $columns;
  }

  function fields() {
    return array(
      'title' => 'The title',
      'abbreviation' => 'The organization abbreviation',
      'attorney' => 'The District Attorney',
    );
  }

  function prepareRow($row) {}
}