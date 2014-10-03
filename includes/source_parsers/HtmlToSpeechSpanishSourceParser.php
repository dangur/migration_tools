<?php
/**
 * @file
 * HtmlToSpeechSpanishSourceParser.
 */

class HtmlToSpeechSpanishSourceParser extends HtmlToSpeechSourceParser {
  /**
   * Dates in spanish speeches are a little different.
   */
  protected function setSpeechDate() {
    try {
      $sds = HtmlCleanUp::extractFirstElement($this->queryPath, '.speechdate');
      if (!empty($sds)) {
        $this->speechDate = JusticeBaseMigration::dojMigrationESDateConvertWDMY($sds);
      }
      else {
        watchdog("doj_migration", "{$this->fileId} failed to acquire a date");
      }
    }
    catch(Exception $e) {
      watchdog("doj_migration", "{$this->fileId} failed to acquire a date :error {$e->getMessage()}");
    }
  }
}