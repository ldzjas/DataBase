SELECT ID||'|'||OrderDate||'|'||lag(OrderDate,1,OrderDate)over(ORDER BY OrderDate)||'|'||ROUND(julianday(OrderDate) - julianday(lag(OrderDate,1,OrderDate)over(ORDER BY OrderDate)),2)
FROM 'Order'
WHERE CustomerId='BLONP'
ORDER BY OrderDate
LIMIT 10;