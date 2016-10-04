<?php

require 'ReolStatisticsMonth.php';

$month = new ReolStatisticsMonth(2016, 9);

print 'Start: ' . date('c', $month->getStartTimestamp()) . "\n";
print 'End: ' . date('c', $month->getEndTimestamp()) . "\n";

$month2 = new ReolStatisticsMonth(2016, 3);

print_r($month2->rangeTo($month));
