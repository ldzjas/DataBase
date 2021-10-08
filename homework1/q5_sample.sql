SELECT CategoryName||'|'||COUNT(CategoryName)||'|'||ROUND(AVG(UnitPrice),2)||'|'||MIN(UnitPrice)||'|'||MAX(UnitPrice)||'|'||SUM(UnitsOnOrder)
FROM Product LEFT JOIN Category
ON Product.CategoryId=Category.Id
GROUP BY Category.Id
HAVING COUNT(Category.Id)>10
ORDER BY Category.Id
