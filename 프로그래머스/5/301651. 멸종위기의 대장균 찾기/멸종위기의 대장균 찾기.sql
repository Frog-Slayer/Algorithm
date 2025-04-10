
-- 코드를 작성해주세요
WITH RECURSIVE GENERATIONS AS (
    SELECT ID, 1 AS GENERATION
    FROM ECOLI_DATA
    WHERE PARENT_ID IS NULL

    UNION ALL

    SELECT E.ID, G.GENERATION + 1
    FROM ECOLI_DATA E
    JOIN GENERATIONS G ON E.PARENT_ID = G.ID
),
NO_CHILD AS (
    SELECT G.ID, G.GENERATION
    FROM GENERATIONS G
    LEFT JOIN ECOLI_DATA E ON G.ID = E.PARENT_ID
    WHERE E.ID IS NULL
)
SELECT COUNT(*) AS COUNT, GENERATION
FROM NO_CHILD
GROUP BY GENERATION
ORDER BY GENERATION;
