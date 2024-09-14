public class MyVisitor extends DemoBaseVisitor<String> {

    @Override
    public String visitPlus(DemoParser.PlusContext ctx) {
        return visitChildren(ctx) + "\nldc " + ctx.right.getText() + "\n" + "iadd";
    }

    @Override
    public String visitNumber(DemoParser.NumberContext ctx) {
        return "ldc " + ctx.number.getText();
    }

    @Override
    protected String aggregateResult(String aggregate, String nextResult) {
        if (aggregate == null) {
            return nextResult;
        }
        if (nextResult == null) {
            return aggregate;
        }
        return aggregate + "\n" + nextResult;
    }

}